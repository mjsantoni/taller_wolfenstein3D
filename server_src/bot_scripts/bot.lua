-- EVENTS --
INVALID = 0
CONNECT_PLAYER = 1
MOVE_PLAYER = 2
SHOOT = 3
OPEN_DOOR = 4
PUSH_WALL = 5
TURN_CAMERA = 6
CHANGE_GUN = 7
PLAYER_READY = 8

MOVE_LEFT = 0
MOVE_RIGHT = 1
MOVE_UP = 2
MOVE_DOWN = 3
CAMERA_LEFT = 1
CAMERA_RIGHT = -1

KNIFE = 1
PISTOL = 2
MACHINE_GUN = 3
CHAIN_GUN = 4
RPG_GUN = 5

-- INFORMACION DEL GAME --
positionables = {}
blockings = {}
players = {}
players_len = 0
position = { x = -1, y = -1 }
angle = 0
self_id = 0
lives = 3

-- VARIABLES DE PROCESAMIENTO --
closest_target = {}
in_sight = {}
in_sight_len = 0
events = {}
destiny_position = { x = -1, y = -1 }
current_equipped_gun_hotkey = PISTOL

-- CONSTANTES --
grid_size = 0
angle_turn = 0
fov = 1
gun_range = 0

first_time = true

--------------------------- SETTERS Y UPDATERS ---------------------------

function setGridSize(size)
    grid_size = size
end

function setAngleTurn(angle_rotation)
    angle_turn = angle_rotation
end

function setGunRange(range)
    gun_range = range
end

function updateAngle(_angle)
    angle = _angle
end

function updateLives(_lives)
    if _lives ~= lives then
        destiny_position.x = position.x
        destiny_position.y = position.y
        lives = _lives
        current_equipped_gun_hotkey = PISTOL
    end
end

function updatePosition(_x, _y)
    position = { x = _x, y = _y }
    --print(string.format("Mi nueva pos es (%s, %s) - ID: %s", position.x, position.y, self_id))
    if first_time then
        --print("Entro a destyiny psoition")
        destiny_position = { x = _x, y = _y }
        first_time = false
    end
end

function setId(_id)
    --io.write("[LUA] Executing setId(".._id..")\n")
    self_id = math.floor(_id)
end

------------------------------- MAPA -------------------------------

function addPositionable(x, y, _type)
    --io.write("[LUA] Executing addPositionable("..x..", "..y..", ".._type..")\n")
    local coord_table = { math.floor(x), math.floor(y) }
    positionables[coord_table] = { type = _type }
    ----print(positionables[coord_table])
end

function addBlocking(x, y, _type)
    --io.write("[LUA] Executing addBlocking("..x..", "..y..", ".._type..")\n")
    local coord_table = { math.floor(x), math.floor(y) }
    blockings[coord_table] = { type = _type }
end

function addPlayer(x, y, _id)
    --io.write("[LUA] Executing addPlayers("..x..", "..y..", ".._id..")\n")
    local coord_table = { math.floor(x), math.floor(y) }
    players[coord_table] = { id = math.floor(_id) }
    players_len = players_len + 1
end

function printMap()
    --print("[LUA] Executing ----printMap()")
    --print("Positionables:")
    for k, v in pairs(positionables) do
        --print(string.format("Coord (%s, %s) -> Type: %s", k[1], k[2], v.type))
    end
    --print("Blockings:")
    for k, v in pairs(blockings) do
        --print(string.format("Coord (%s, %s) -> Type: %s", k[1], k[2], v.type))
    end
    --print("Players:")
    for k, v in pairs(players) do
        --print(string.format("Coord (%s, %s) -> ID: %s", k[1], k[2], v.id))
    end
end

function cleanMap()
    --print(string.format("Coord mias(%s, %s)", position.x, position.y))
    --print(string.format("Coord objetivo(%s, %s)", destiny_position.x, destiny_position.y))
    positionables = {}
    blockings = {}
    players = {}
    players_len = 0
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
    local coord_table = { x_norm, y_norm }
    return isInTable(blockings, x_norm, y_norm)
end

function getDiff(x_old, y_old, x_new, y_new)
    local x_diff = math.abs(x_old - x_new)
    local y_diff = math.abs(y_old - y_new)
    return (x_diff + y_diff)
end

----------------------------------- SIMULATE -----------------------------------

function getEvents()
    return events
end

function createChangeGunEvent(hotkey)
    table.insert(events, CHANGE_GUN)
    table.insert(events, self_id)
    table.insert(events, hotkey)
end

function closestTarget()

    in_sight = {}
    in_sight_len = 0
    events = {}
    closest_target = {}

    --io.write("[LUA] Executing closestTarget - ID: "..self_id.."\n")
    if lives == 0 or players_len == 0 then
        return
    end

    if not (destiny_position.x == position.x and destiny_position.y == position.y) then
        return
    end

    if current_equipped_gun_hotkey ~= KNIFE then
        createChangeGunEvent(KNIFE)
        current_equipped_gun_hotkey = KNIFE
    end

    local min_difference = math.huge
    --io.write("[LUA] Estoy en("..position.x..", "..position.y..") - ID: "..self_id.."\n")

    for coord, player in pairs(players) do
        --io.write("[LUA] Calling isInSight("..coord[1]..", "..coord[2]..", "..position.x..", "..position.y..") - ID: "..self_id.."\n")
        found_in_sight = math.floor(isInSight(coord[1], coord[2], position.x, position.y))
        --io.write("[LUA] isInSight returned "..found_in_sight.." - ID: "..self_id.."\n")

        if (found_in_sight == 1) then
            in_sight[coord] = true
            in_sight_len = in_sight_len + 1
        end
    end

    if in_sight_len > 0 then
        for coord, _ in pairs(in_sight) do
            difference = getDiff(coord[1], coord[2], position.x, position.y)
            --print(string.format("For (in_sight) iteration with diff: %s - ID: %s", difference, self_id))
            if difference < min_difference then
                -- Aca muere, no hace mas nada
                --io.write("[LUA] Min diff is: "..difference.." AND Closest target IN SIGHT is: "..coord[1]..", "..coord[2].." - ID: "..self_id.."\n")
                min_difference = difference
                closest_target = coord
            end
        end
    else
        for coord, _ in pairs(players) do
            difference = getDiff(coord[1], coord[2], position.x, position.y)
            --print(string.format("For (players) iteration (no players in sight) with diff: %s - ID: %s", difference, self_id))
            if difference < min_difference then
                --io.write("[LUA] Min diff is: "..difference.." AND Closest target NO SIGHT is: "..coord[1]..", "..coord[2].." - ID: "..self_id.."\n")
                min_difference = difference
                closest_target = coord
            end
        end
    end

    --print(string.format("Finished closestTarget, calling simulatePlayer - ID: %s", self_id))
    simulatePlayer(closest_target[1], closest_target[2], min_difference)
    --io.write("[LUA] Al final quede en  ("..position.x..", "..position.y..") - ID: "..self_id.."\n")
    destiny_position.x = position.x
    destiny_position.y = position.y
end

function createPicanazoEvent()
    table.insert(events, SHOOT)
    table.insert(events, self_id)
    table.insert(events, INVALID)
end

function createRotateCameraEvent(amount, rotation)
    for i = 1, amount do
        table.insert(events, TURN_CAMERA)
        table.insert(events, self_id)
        table.insert(events, rotation)
    end
end

function createMoveEvent()
    --print("Cree un moveevent")
    table.insert(events, MOVE_PLAYER)
    table.insert(events, self_id)
    table.insert(events, MOVE_UP)
end

function simulatePlayer(enemy_x, enemy_y, min_difference)
    --print(string.format("Entre a simulatePlayer - ID: %s", self_id))
    for i = 1, 2 do
        if playerInSight(enemy_x, enemy_y) and playerInRange(enemy_x, enemy_y) then
            createPicanazoEvent()
            --print(string.format("LO VEOOOOOOOOOOOOO - ID: %s", self_id))
            break
        end
        getDirectionAndMove(enemy_x, enemy_y, min_difference)
    end

end

function playerInRange(x, y)
    local distance = getDiff(position.x, position.y, x, y)
    return distance <= gun_range
end

function playerInSight(x, y)
    local angle_between = angleBetween(position.x, position.y, x, y)
    return insideAngle(angle, angle_between)
end

function insideAngle(facing, target)
    local dot = math.cos(facing) * math.cos(target) + math.sin(facing) * math.sin(target)
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
--]]

function moveToPosition(x, y, angle)
    local new_x, new_y = move(position.x, position.y, angle)
    --io.write("[LUA] moveToPosition new recv Coord: ("..math.floor(new_x)..", "..math.floor(new_y)..") - ID: "..self_id.."\n")
    return math.floor(new_x), math.floor(new_y)
end

function getDirectionAndMove(destiny_x, destiny_y, min_difference)
    ----io.write("[LUA] Executing getDirectionAndMove with ("..destiny_x..", "..destiny_y..") and min_diff: "..min_difference.." - ID: "..self_id.."\n")

    -- Create all tries to move and get distances
    --io.write("[LUA] El angulo de front es ("..angle..")\n")
    local x_move_front, y_move_front = moveToPosition(position.x, position.y, angle)
    local diff_front = getDiff(x_move_front, y_move_front, destiny_x, destiny_y)
    if getDiff(x_move_front, y_move_front, position.x, position.y) == 0 then
        --io.write("diff_self_front is 0, changing to inf - ID: "..self_id.."\n")
        diff_front = math.huge
    end
    --io.write("diff_front is now: "..diff_front.." - ID: "..self_id.."\n")

    local x_move_right, y_move_right = moveToPosition(position.x, position.y, angle - angle_turn)
    local diff_right = getDiff(x_move_right, y_move_right, destiny_x, destiny_y)
    if getDiff(x_move_right, y_move_right, position.x, position.y) == 0 then
        --io.write("diff_self_right is 0, changing to inf - ID: "..self_id.."\n")
        diff_right = math.huge
    end
    --io.write("diff_right is now: "..diff_right.." - ID: "..self_id.."\n")

    local x_move_left, y_move_left = moveToPosition(position.x, position.y, angle + angle_turn)
    local diff_left = getDiff(x_move_left, y_move_left, destiny_x, destiny_y)
    if getDiff(x_move_left, y_move_left, position.x, position.y) == 0 then
        --io.write("diff_self_left is 0, changing to inf - ID: "..self_id.."\n")
        diff_left = math.huge
    end
    --io.write("diff_left is now: "..diff_left.." - ID: "..self_id.."\n")

    local turns_needed_to_back = math.floor(1 / (angle_turn / math.pi))
    --io.write("ANGULOS PARA BACK"..turns_needed_to_back.." \n")
    local x_move_back, y_move_back = moveToPosition(position.x, position.y, angle + turns_needed_to_back * angle_turn)
    local diff_back = getDiff(x_move_back, y_move_back, destiny_x, destiny_y)
    if getDiff(x_move_back, y_move_back, position.x, position.y) == 0 then
        --io.write("diff_self_back is 0, changing to inf\n")
        diff_back = math.huge
    end
    --io.write("diff_back is now: "..diff_back.."\n")

    -- Verify which is the lowest
    if diff_front <= diff_left and diff_front <= diff_right and diff_front <= diff_back then
        --io.write("diff_front is the lowest: "..diff_front.." - ID: "..self_id.."\n")
        --print(string.format("Voy a avanzar derechito nomas culeado %s", self_id))
        updatePosition(x_move_front, y_move_front)

    elseif diff_left <= diff_front and diff_left <= diff_right and diff_left <= diff_back then
        --io.write("diff_left is the lowest: "..diff_left.." - ID: "..self_id.."\n")
        angle = addAngleToCurrent(angle_turn)
        local angle_moves = tryRotations(diff_left, destiny_x, destiny_y, 1)
        createRotateCameraEvent(angle_moves + 1, CAMERA_LEFT) -- 1 es CAMERA_LEFT
        local x_move, y_move = moveToPosition(position.x, position.y, angle)
        updatePosition(x_move, y_move)

    elseif diff_right <= diff_front and diff_right <= diff_left and diff_right <= diff_back then
        --io.write("diff_right is the lowest: "..diff_right.." - ID: "..self_id.."\n")
        angle = addAngleToCurrent(-1 * angle_turn)
        local angle_moves = tryRotations(diff_right, destiny_x, destiny_y, -1)
        createRotateCameraEvent(angle_moves + 1, CAMERA_RIGHT) -- -1 es CAMERA_RIGHT
        local x_move, y_move = moveToPosition(position.x, position.y, angle)
        updatePosition(x_move, y_move)
    else
        --io.write("diff_back is the lowest: "..diff_back.."\n")
        angle = addAngleToCurrent(turns_needed_to_back * angle_turn)
        createRotateCameraEvent(turns_needed_to_back, CAMERA_LEFT)
        updatePosition(x_move_back, y_move_back)
    end
    createMoveEvent()

end

----------------------------------- ANGLES -----------------------------------

function tryRotations(difference, destiny_x, destiny_y, rotation_factor)
    local acum = 0
    local x_move
    local y_move
    while true do
        x_move, y_move = moveToPosition(position.x, position.y, addAngleToCurrent(rotation_factor * angle_turn))
        local diff = getDiff(x_move, y_move, destiny_x, destiny_y)
        if getDiff(x_move, y_move, position.x, position.y) == 0 then
            diff = math.huge
        end
        if diff < difference then
            acum = acum + 1
            angle = addAngleToCurrent(rotation_factor * angle_turn)
            difference = diff
        else
            break
        end
    end
    --io.write("Acumulador es: "..acum.." - ID: "..self_id.."\n")
    return acum
end

----------------------------------- AUX -----------------------------------

function addAngleToCurrent(_angle)
    local temporal = angle + _angle
    if (temporal > 2 * math.pi) then
        temporal = temporal - 2 * math.pi
    elseif (temporal < 0) then
        temporal = temporal + 2 * math.pi
    end
    return temporal
end

function angleBetween(x1, y1, x2, y2)
    local new_x = (-x1) - (-x2)
    local new_y = (y1) - (y2)
    return math.deg(math.atan2(new_y, new_x))
end

function is_int(n)
    return (type(n) == "number") and (math.floor(n) == n)
end

function split (inputstr, sep)
    if sep == nil then
        sep = "%s"
    end
    local t = {}
    for str in string.gmatch(inputstr, "([^" .. sep .. "]+)") do
        table.insert(t, str)
    end
    return t
end
