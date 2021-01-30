mapa = {}
players = {}

function addToMap(r1, r2, r3, r4)
	io.write("[LUA] Executing addToMap("..r1..", "..r2..", "..r3..", "..r4..")\n")
	local coord_table = {r3, r4}
	mapa[r1] = {type = r2, coord = coord_table}
	--return r1 * r2
end

function printMap()
	print("[LUA] Executing printMap()")
	print("Tengo en mi mapa:")
	for k, v in pairs(mapa) do
		print(string.format("Id: %s -> Tipo: %s, Coord: (%s, %s)", k, v.type, v.coord[1], v.coord[2]))
	end
end

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