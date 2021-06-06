local require = GLOBAL.require

-- Lights Out Full Moon fix

Clock = require("components/clock")

local SuperStartNight = Clock.StartNight
function Clock:StartNight(instant, fromnightvision)
	if self:CurrentPhaseIsAlways() then
		self.previous_phase = ""
	end
	SuperStartNight(self, instant, fromnightvision)
end