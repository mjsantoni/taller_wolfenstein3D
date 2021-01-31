mapa = {}
players = {}

function addToMap(r1, r2, r3, r4)
	io.write("[LUA] Executing addToMap("..r1..", "..r2..", "..r3..", "..r4..")\n")
	local coord_table = {r3, r4}
	mapa[coord_table] = {type = r2, id = r1}
	--return r1 * r2
end

function printMap()
	print("[LUA] Executing printMap()")
	print("Tengo en mi mapa:")
	for k, v in pairs(mapa) do
		print(string.format("Coord (%s, %s) -> Type: %s - ID: %s", k[1], k[2], v.type, v.id))
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