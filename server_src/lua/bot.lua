-- INFORMACION DEL GAME --
positionables = {}
blockings = {}
players = {}
position = {x = 96, y = 96}
angle = 0

-- VARIABLES DE PROCESAMIENTO --
closest_target = {}
straight_line = {}
in_sight = {}
in_sight_len = 0

-- CONSTANTES --
self_id = 0
grid_size = 64
angle_turn = math.pi / 8
fov = 1 -- en radianes
gun_range = 20


function addPositionable(x, y, _type)
	io.write("[LUA] Executing addPositionable("..x..", "..y..", ".._type..")\n")
	local coord_table = {math.floor(x), math.floor(y) }
	positionables[coord_table] = {type = _type}
	print(positionables[coord_table])
end

function addBlocking(x, y, _type)
	io.write("[LUA] Executing addBlocking("..x..", "..y..", ".._type..")\n")
	local coord_table = {math.floor(x), math.floor(y)}
	blockings[coord_table] = {type = _type}
end

function addPlayer(x, y, _id)
	io.write("[LUA] Executing addPlayers("..x..", "..y..", ".._id..")\n")
	local coord_table = {math.floor(x), math.floor(y)}
	players[coord_table] = {id = math.floor(_id)}
end

function setId(_id)
	io.write("[LUA] Executing setId(".._id..")\n")
	self_id = id
end

function updateAngle(_angle)
	angle = _angle
end

function cleanMap()
	positionables = {}
	blockings = {}
	players = {}
end

function updatePosition(_x, _y)
	position = {x = _x, y = _y }
	print(string.format("Mi nueva pos es (%s, %s)", position.x, position.y))
end

function printMap()
	print("[LUA] Executing printMap()")
	print("Positionables:")
	for k, v in pairs(positionables) do
		print(string.format("Coord (%s, %s) -> Type: %s", k[1], k[2], v.type))
	end
	print("Blockings:")
	for k, v in pairs(blockings) do
		print(string.format("Coord (%s, %s) -> Type: %s", k[1], k[2], v.type))
	end
	print("Players:")
	for k, v in pairs(players) do
		print(string.format("Coord (%s, %s) -> ID: %s", k[1], k[2], v.id))
	end
end

------------------------------- Calculos -------------------------------

function isInTable(tab, x, y)
	for key, value in pairs(tab) do
		if key[1] == x and key[2] == y then
			return true
		end
	end
	return false
end

function normalizedCoordinate(i)
	local normalized = (math.floor(i / grid_size)) * grid_size
	return normalized
end

function isABlockingItemAt(x, y)
	local x_norm = (normalizedCoordinate(x))
	local y_norm = (normalizedCoordinate(y))
	--io.write("[LUA] Coord: ("..x_norm..", "..y_norm..")\n")
	local coord_table = {x_norm, y_norm }
	return isInTable(blockings, x_norm, y_norm)
end

function getDiff(x_old, y_old, x_new, y_new)
	local x_diff = math.abs(x_old - x_new)
	local y_diff = math.abs(y_old - y_new)
	return (x_diff + y_diff)
end

----------------------------------- SIMULATE -----------------------------------

function closestTarget()
	in_sight_len = 0
	local min_difference = math.huge
	io.write("[LUA] Executing closestTarget\n")

	for coord, player in pairs(players) do
		io.write("[LUA] Calling isInSight("..coord[1]..", "..coord[2]..", "..position.x..", "..position.y..")\n")
		found_in_sight = math.floor(isInSight(coord[1],coord[2],position.x,position.y))
		io.write("[LUA] isInSight returned "..found_in_sight.."\n")

		if (found_in_sight == 1) then
			in_sight[coord] = true
			in_sight_len = in_sight_len + 1
		end
	end
	if in_sight_len > 0 then
		for coord, _ in pairs(in_sight) do
			difference = getDiff(coord[1], coord[2], position.x, position.y)
			print(string.format("For (in_sight) iteration with diff: %s", difference))
			if difference < min_difference then -- Aca muere, no hace mas nada
				io.write("[LUA] Min diff is: "..difference.."\n[LUA] Closest target is: "..coord[1]..", "..coord[2].."\n")
				min_difference = difference
				closest_target = coord
			end
		end
	else
		for coord, _ in pairs(players) do
			difference = getDiff(coord[1], coord[2], position.x, position.y)
			print(string.format("For (players) iteration (no players in sight) with diff: %s", difference))
			if difference < min_difference then
				io.write("[LUA] Min diff is: "..difference.."\n[LUA] Closest target is: "..coord[1]..", "..coord[2].."\n")
				min_difference = difference
				closest_target = coord
			end
		end
	end

	print("Finished closestTarget, calling simulatePlayer")
	simulatePlayer(closest_target[1], closest_target[2], min_difference)
end

function simulatePlayer(enemy_x, enemy_y, min_difference)
	print("Entre a simulatePlayer")
	for i=1,6 do
		if playerInSight(enemy_x, enemy_y) and playerInRange(enemy_x, enemy_y) then
			--createPicanazoEvent()
			print("LO VEOOOOOOOOOOOOO")
			break
		end
		getDirectionAndMove(enemy_x, enemy_y, min_difference)
	end

end

function playerInRange(x, y)
	local distance = getDiff(position.x, position.y, x, y)
	return distance <= gun_range
end

function playerInSight(x,y)
	local angle_between = angleBetween(position.x, position.y, x, y)
	return insideAngle(angle, angle_between)
end

function insideAngle(facing, target)
	local dot = math.cos(facing)*math.cos(target) + math.sin(facing)*math.sin(target)
	local interval = math.acos(dot)
	return interval <= fov
end


--[[
Siempre tiene un objetivo: closest target carga el mas cercano y
 llamo a moveToTarget que ejecuta un numero random entre 1 y 5 el getDirectionAndMove
 para tratar de acercarse

Las funciones de getDirectionAndMove usan el move to position del col handler

funciones de crear eventos son llamadas por las funciones q mueven, devuelven
eventos liso y llano con los ints

]]--

function moveToPosition(x, y, angle)
	local new_x, new_y = move(position.x, position.y, angle)
	io.write("[LUA] moveToPosition new recv Coord: ("..math.floor(new_x)..", "..math.floor(new_y)..")\n")
	return math.floor(new_x), math.floor(new_y)
end

function getDirectionAndMove(destiny_x, destiny_y, min_difference)
	io.write("[LUA] Executing getDirectionAndMove with ("..destiny_x..", "..destiny_y..") and min_diff: "..min_difference.."\n")

	-- Create all tries to move and get distances
	local x_move_front, y_move_front = moveToPosition(position.x, position.y, angle)
	local diff_front = getDiff(x_move_front, y_move_front, destiny_x, destiny_y)
	if getDiff(x_move_front, y_move_front, position.x, position.y) == 0 then
		io.write("diff_self_front is 0, changing to inf\n")
		diff_front = math.huge
	end
	io.write("diff_front is now: "..diff_front.."\n")

	local x_move_right, y_move_right = moveToPosition(position.x, position.y, angle - angle_turn)
	local diff_right = getDiff(x_move_right, y_move_right, destiny_x, destiny_y)
	if getDiff(x_move_right, y_move_right, position.x, position.y) == 0 then
		io.write("diff_self_right is 0, changing to inf\n")
		diff_right = math.huge
	end
	io.write("diff_right is now: "..diff_right.."\n")

	local x_move_left, y_move_left = moveToPosition(position.x, position.y, angle + angle_turn)
	local diff_left = getDiff(x_move_left, y_move_left, destiny_x, destiny_y)
	if getDiff(x_move_left, y_move_left, position.x, position.y) == 0 then
		io.write("diff_self_left is 0, changing to inf\n")
		diff_left = math.huge
	end
	io.write("diff_left is now: "..diff_left.."\n")

	-- Verify which is the lowest
	if diff_front <= diff_left and diff_front <= diff_right and diff_front then
		io.write("diff_front is the lowest: "..diff_front.."\n")
		print("Voy a avanzar derechito nomas culeado")
		updatePosition(x_move_front, y_move_front)

	elseif diff_left <= diff_front and diff_left <= diff_right and diff_left then
		io.write("diff_left is the lowest: "..diff_left.."\n")
		angle = addAngleToCurrent(angle_turn)
		local angle_moves = tryRotations(diff_left, destiny_x, destiny_y, 1)
		createRotateCameraEvent(angle_moves + 1, 1) -- 1 es CAMERA_LEFT
		local x_move, y_move = moveToPosition(position.x, position.y, angle)
		updatePosition(x_move, y_move)

	elseif diff_right <= diff_front and diff_right <= diff_left and diff_right then
		io.write("diff_right is the lowest: "..diff_right.."\n")
		angle = addAngleToCurrent(-1*angle_turn)
		local angle_moves = tryRotations(diff_right, destiny_x, destiny_y, -1)
		createRotateCameraEvent(angle_moves + 1, -1) -- -1 es CAMERA_RIGHT
		local x_move, y_move = moveToPosition(position.x, position.y, angle)
		updatePosition(x_move, y_move)
	end
	createMoveEvent()

end

----------------------------------- ANGLES -----------------------------------

function tryRotations(difference, destiny_x, destiny_y, rotation_factor)
	local acum = 0
	local x_move
	local y_move
	while true do
		x_move, y_move = moveToPosition(position.x, position.y, addAngleToCurrent(rotation_factor*angle_turn))
		local diff = getDiff(x_move, y_move, destiny_x, destiny_y)
		if getDiff(x_move, y_move, position.x, position.y) == 0 then
			diff = math.huge
		end
		if diff < difference then
			acum = acum + 1
			angle = addAngleToCurrent(rotation_factor*angle_turn)
			difference = diff
		else
			break
		end
	end
	io.write("Acumulador es: "..acum.."\n")
	return acum
end


----------------------------------- AUX -----------------------------------

function addAngleToCurrent(_angle)
	local temporal = angle + _angle
	if (temporal > 2*math.pi) then
		temporal = temporal - 2*math.pi
	elseif (temporal < 0) then
		temporal = temporal + 2*math.pi
	end
	return temporal
end

function angleBetween(x1, y1, x2, y2)
	local new_x = (-x1) - (-x2)
	local new_y = (y1) - (y2)
	return math.deg(math.atan2(new_y,new_x))
end


function is_int(n)
	return (type(n) == "number") and (math.floor(n) == n)
end

function split (inputstr, sep)
	if sep == nil then
		sep = "%s"
	end
	local t={}
	for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
		table.insert(t, str)
	end
	return t
end