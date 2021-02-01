positionables = {}
blockings = {}
players = {}
self_id = 0
grid_size = 64
straight_line = {}
closest_target = {}
position = {}
in_sight = {}
in_sight_len = 0
angle = 0
angle_turn = 0
position = {x = 160, y = 160}

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
	players[coord_table] = {id = _id}
end

function setId(_id)
	io.write("[LUA] Executing setId(".._id..")\n")
	self_id = id
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
	-- PRUEBA DE BLOCKING PAPA --
	--[[
	for k, v in pairs(players) do
		if isABlockingItemAt(k[1], k[2]) then
			print("SI HAY BLOKING ITEM EN PLAYER")
		else
			print("NO HAY BLOCKING ITEM EN PLAYER")
		end
	end

	for k, v in pairs(blockings) do
		if isABlockingItemAt(k[1], k[2]) then
			print("SI HAY BLOKING ITEM EN BLOKING")
		else
			print("NO HAY BLOCKING ITEM EN BLOKIN")
		end
	end
	--]]
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


function executeClosestTarget(x_old, y_old, x_new, y_new)
	io.write("[LUA] Calling isInSight("..x_old..", "..y_old..", "..x_new..", "..y_new..")\n")
	return_value = isInSight(x_old,y_old,x_new,y_new)
	return_value = math.floor(return_value)
	if return_value == 1 then
		io.write("[LUA] isInSight returned "..return_value.."\n")
	else
		io.write("[LUA] isInSight returned NOOO\n")
	end
	getDiff(1,2,3,4)
end


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
			print("Calling getDiff")
			difference = getDiff(coord[1], coord[2], position.x, position.y)
			print(string.format("For de in sight con diff: %s", difference))
			if difference < min_difference then -- Aca muere, no hace mas nada
				io.write("[LUA] Min diff is: "..difference.."\n[LUA] Closest target is: "..coord[1]..", "..coord[2].."\n")
				min_difference = difference
				closest_target = coord
			end
		end
	else
		for coord, _ in pairs(players) do
			print("No veo gente llamo con players a getDiff")
			difference = getDiff(coord[1], coord[2], position.x, position.y)
			if difference < min_difference then
				min_difference = difference
				closest_target = coord
			end
		end
	end

	io.write("[LUA] Min diff is: "..difference.."\n[LUA] Closest target is: "..coord[1]", "..coord[2].."\n")
end



--[[
function tryMove()
	difference = math.huge

	diff_front = getDiff(moveFront(positon.x, poisition.y),position.x, position.y )
	diff_front_left = getDiff(moveFrontLeft(positon.x, poisition.y),position.x, position.y )
	diff_front_right = getDiff(moveFrontRight(positon.x, poisition.y),position.x, position.y )

	if diff_front <= diff_front_left and diff_front <= diff_front_right:
		tryFront()
		create_moveEvent()

	if diff_front_left < diff_front and diff_front_left < diff_front_right:
		angles_move = tryLeft()
		create_TurnLeftEvent(4)
		create_moveEvent()

	angles_move = tryRight()
	create_TurnRightEvent(4) // crea 4 eventos de giro derecha
	create_moveEvent() // crea 1 evento de avanzar

	if inRange(closest_target)
		create_pikanazoEvent()
	
--]]


----------------------------------- AUX -----------------------------------

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