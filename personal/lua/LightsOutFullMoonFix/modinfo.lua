name = "Lights Out Bug Fixes and Tweaks"
description = "Bug fixes and tweaks for Always Night"
author = "chandl34"
version = "1.0.1"
api_version = 6
api_version_dst = 10
priority = 0

dont_starve_compatible = true
reign_of_giants_compatible = true
shipwrecked_compatible = true
hamlet_compatible = true
dst_compatible = false

all_clients_require_mod = false
client_only_mod = true

server_filter_tags = {}

icon_atlas = "modicon.xml"
icon = "modicon.tex"

forumthread = "files/file/2026-lights-out-full-moon-bug-fix/"

configuration_options =
{
	{
		name = "CAVELIGHT_MATCHES_OUTSIDE",
		label = "Cavelight",
		hover = "Cavelight behavior",
		options = 
		{
			{description = "Like Outside", data = true},
			{description = "Default", data = false},
		},
		default = false,
	},	
}