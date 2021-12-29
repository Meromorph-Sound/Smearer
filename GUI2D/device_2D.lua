format_version = "2.0"



front = {
  Bg = { {path = "front1U"} },
  onoffbypass = {offset = {200,20},{path="Fader_Bypass_3frames", frames = 3 }},
  patches = { offset = { 500,10},{ path = "PatchBrowseGroup", frames = 1}},
  patch = { offset = {805,10},{ path = "PatchName_1frames",frames=1}},
  deviceName = {offset = { 1900, 10 },{ path = "Tape_Horizontal_1frames", frames = 1 }},
  half_width = {offset = { 900, 135 },{ path = "Knob_01_63frames", frames = 63 }},
  n_oscillators = {offset = { 1200, 135 },{ path = "Knob_01_63frames", frames = 63 }},
  scale_factor = {offset = { 1500, 125 },{ path = "Knob_01_63frames", frames = 63 }},
  window_display = {offset={1900,140},{path="Windows_6frames", frames=6 }},
  window   = { offset = {2200,140}, { path = "UpDown", frames = 3}},
  filter_on = {offset={2850,50}, {path="Button_53_2frames", frames=2 }},
  filter_q = {offset = { 2850, 135 },{ path = "Knob_01_63frames", frames = 63 }},
  limiter_on = {offset={3200,50}, {path="Button_53_2frames", frames=2 }},
  limiter = {offset = { 3200, 135 },{ path = "Knob_01_63frames", frames = 63 }},
  limiter_hs = {offset={3400,200}, {path="Button_53_2frames", frames=2 }},
  
}
back = {
  Bg = { {path = "backPanel"} },
  Placeholder = {offset = { 2000, 100 },{ path = "Placeholder" }},
  deviceName = {offset = { 180, 230 },{ path = "Tape_Horizontal_1frames", frames = 1 }},
  audioInputL = {offset = { 1000,120 },{ path = "SharedAudioJack", frames = 3 }},
  audioInputR = {offset = { 1200,120 },{ path = "SharedAudioJack", frames = 3 }},
  audioOutputL = {offset = { 1550,120 },{ path = "SharedAudioJack", frames = 3 }},
  audioOutputR = {offset = { 1750,120  },{ path = "SharedAudioJack", frames = 3 }}
}

folded_front = {
  Bg = {{ path = "Panel_Folded_Back" }},
  patches = { offset = { 700,24},{ path = "PatchBrowseGroup", frames = 1}},
  patch = { offset = {1005,24},{ path = "PatchName_1frames",frames=1}},
  deviceName = { offset = { 2800, 42}, { path = "Tape_Horizontal_1frames", frames = 1 }},
}
folded_back = { 
  Bg = {{ path = "Panel_Folded_Back" }},
  CableOrigin = { offset = { 1885, 75 }}
}





