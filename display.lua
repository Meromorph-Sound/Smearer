format_version = "1.0"

local Axes = { r=180,g=180,b=180 }
local Rect = { r=80,g=80,b=80,a = 64 }
local Graph = { r=0,g=255,b=0  }

function clip(value)
  return math.max(0,math.min(1,value))
end


function drawVolume(property_values,display_info,dirty_rect)
  local volume=clip(property_values[1])
  local w = display_info.width
  local h = display_info.height
  
  local width = w*volume
  jbox_display.draw_rect({left= 0, top= 0, right= width, bottom= h-1},Graph)
  
end

-- extend this to a stereo version, then I can have two, one for input, the other for output
--
--jbox.custom_display {
--      graphics={node="volume"},
--      display_width_pixels=300,
--      display_height_pixels=40,
--      values = { "/custom_properties/volume" },
--      draw_function = "drawVolume"
--    },
--
--  volume = {
--    offset = {700,54},
--    { path = "Display_200_50_1frames", frames = 1 }
--  },