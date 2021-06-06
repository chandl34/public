-- Lights Out Full Moon fix

local require = GLOBAL.require


--- Members
local origin_modes = 
{
	survival = "survival",
	cave = "survival",
	shipwrecked = "shipwrecked",
	volcano = "shipwrecked",
	porkland = "porkland",
}
	
local fixedDaySettings = false
local CAVELIGHT_MATCHES_OUTSIDE = GetModConfigData("CAVELIGHT_MATCHES_OUTSIDE")
	
	
--- Helper 
local function GetDayMode()
	local day = "default"
	
	local slot = GLOBAL.SaveGameIndex:GetCurrentSaveSlot()
	local mode = GLOBAL.SaveGameIndex:GetCurrentMode()
	local base_mode = CAVELIGHT_MATCHES_OUTSIDE and origin_modes[mode] or mode	
	local options = GLOBAL.SaveGameIndex:GetModeData(slot, base_mode).options		
	if options ~= nil and GLOBAL.GetTableSize(options) > 0 then	
		local levels = require("map/levels")
		local preset = options["preset"]
		for i, level in pairs(levels.sandbox_levels) do	
			if level.id == preset then	
				local overrides = level.overrides				
				for j, override in pairs(overrides) do	
					if override[1] == "day" then
						day = override[2]
					end
				end		
				break
			end
		end	
		
		if options["tweak"] ~= nil and options["tweak"]["misc"] ~= nil and options["tweak"]["misc"]["day"] ~= nil then
			day = options["tweak"]["misc"]["day"]
		end				
	end	
	
	return day	
end

local function FixDaySettings()	
	local day = GetDayMode()
	local retune = require("tuning_override")  
	retune.OVERRIDES["day"].doit(day)
end


--- Cavelight
AddPrefabPostInit("cavelight", function(inst)
    inst:ListenForEvent("nighttime", function()
		if CAVELIGHT_MATCHES_OUTSIDE and GLOBAL.GetClock():GetMoonPhase() == "full" then		
			inst.Light:Enable(true)
			inst.components.lighttweener:StartTween(nil, 5, .6, .6, {84/255,  122/255, 156/255}, 4)
		end			
	end, GLOBAL.GetWorld())
end)


--- Clock 
local Clock = require("components/clock")

local SuperStartNight = Clock.StartNight
function Clock:StartNight(instant, fromnightvision)
	if self:CurrentPhaseIsAlways() then
		self.previous_phase = ""
	end
	SuperStartNight(self, instant, fromnightvision)
end

local SuperOnUpdate = Clock.OnUpdate
function Clock:OnUpdate(dt)
	SuperOnUpdate(self, dt)

	if fixedDaySettings == false then
		fixedDaySettings = true
		
		-- TODO fix bug
		local oldSettings = 
		{ 
			day = self:GetDaySegs(),
			dusk = self:GetDuskSegs(),
			night = self:GetNightSegs(),
		}
		
		FixDaySettings()	
		
		local newSettings = 
		{ 
			day = self:GetDaySegs(),
			dusk = self:GetDuskSegs(),
			night = self:GetNightSegs(),
		}
		
		if	oldSettings["day"] == newSettings["day"] and 
			oldSettings["dusk"] == newSettings["dusk"] and 
			oldSettings["night"] == newSettings["night"] then
			print("Skipping update")
			return
		end
		
		print("Updated day settings (", GetDayMode(), ")")	
		--[[
        if self.phase == "day" then
            self:StartDay()
        elseif self.phase == "dusk" then
            self:StartDusk()
        else
            self:StartNight()
        end
		]]--
	end
end
