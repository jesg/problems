local lapis = require("lapis")
local app = lapis.Application()

app:get("/", function()
  return "Welcome to Lapis " .. require("lapis.version")
end)

app:get("/:id/.+", function(self)
	local nodes = ngx.shared.nodes
	local ip_addr, err, forcible = nodes:get(self.params.id)
	if not ip_addr then
		return { status = 404 }
	end
	ngx.var.node = ip_addr
end)


return app
