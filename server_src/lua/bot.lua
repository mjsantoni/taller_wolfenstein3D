positionables = {}
blockings = {}
players = {}
self_id = 0

function addPositionable(x, y, _type)
	io.write("[LUA] Executing addPositionable("..x..", "..y..", ".._type..")\n")
	local coord_table = {x, y}
	positionables[coord_table] = {type = _type}
end

function addBlocking(x, y, _type)
	io.write("[LUA] Executing addBlocking("..x..", "..y..", ".._type..")\n")
	local coord_table = {x, y}
	blockings[coord_table] = {type = _type}
end

function addPlayer(x, y, _id)
	io.write("[LUA] Executing addPlayers("..x..", "..y..", ".._id..")\n")
	local coord_table = {x, y}
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

end

------------------------------- Calculos -------------------------------

-- Hacer estas funciones en lua
--[[
bool Map::isABlockingItemAt(const Coordinate& coordinates) {
	Coordinate normalize = getNormalizedCoordinate(coordinates);
if(board.find(normalize) != board.end())
	return board.at(normalize).isBlocking();
return false;
}
Coordinate Map::getNormalizedCoordinate(Coordinate coordinates) {
int x_normalize = trunc(coordinates.x / grid_size) * grid_size;
int y_normalize = trunc(coordinates.y / grid_size) * grid_size;
Coordinate normalize(x_normalize, y_normalize);
return normalize;
}
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