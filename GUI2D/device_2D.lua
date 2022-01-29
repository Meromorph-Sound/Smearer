format_version = "2.0"



front = {
  Bg = { {path = "front2U"} },
  onoffbypass = {offset = {200,20},{path="Fader_Bypass_3frames", frames = 3 }},
  patches = { offset = { 500,20},{ path = "PatchBrowseGroup", frames = 1}},
  patch = { offset = {805,20},{ path = "PatchName_1frames",frames=1}},
  deviceName = {offset = { 50,150 },{ path = "Tape_Vertical_1frames", frames = 1 }},
  
  half_width = {offset = { 500, 160 },{ path = "Knob_14_63frames", frames = 63 }},
  n_oscillators = {offset = { 750, 160 },{ path = "Knob_14_63frames", frames = 63 }},
  scale_factor = {offset = { 1000, 160 },{ path = "Knob_14_63frames", frames = 63 }},
  mixer = {offset = { 500, 440 },{ path = "Fader_09_60frames", frames = 60 }},
  
  window_display = {offset={2710,290},{path="Windows_6frames", frames=6 }},
  window   = { offset = {3165,305}, { path = "UpDown", frames = 3}},
  
  filter_on = {offset={1250,440}, {path="Button_53a_2frames", frames=2 }},
  filter_1 = {offset  ={1250, 550 }, {path="Button_102_2frames",frames=2}},
  filter_2 = {offset  ={1350, 550 }, {path="Button_103_2frames",frames=2}},
  filter_q = {offset = { 1620, 475 },{ path = "Knob_49_63frames", frames = 63 }},
  
  limiter_on = {offset={1250,190}, {path="Button_53a_2frames", frames=2 }},
  limiter = {offset = { 1620, 195 },{ path = "Knob_49_63frames", frames = 63 }},
  limiter_hs = {offset={1250,310}, {path="Button_53a_2frames", frames=2 }},
  
  duration_min = {offset = { 1950,80 },{ path = "Knob_49_63frames", frames = 63 }},
  duration_range = {offset = { 2300,80 },{ path = "Knob_49_63frames", frames = 63 }},
  duration_min_display = {offset={1950,240},{path="Display_200_50_1frames"}},
  duration_range_display = {offset={2300,240},{path="Display_200_50_1frames"}},
  
  waveform_display = {offset={2710,95}, {path="Display_51_9frames",frames=9}},
  waveform   = { offset = {2895,103}, { path = "UpDown", frames = 3}},
  
  silence = {offset = { 1950,450 },{ path = "Knob_49_63frames", frames = 63 }},
  silence_on = {offset = { 2210,395 },{ path = "Lamp_10_GREEN_2frames", frames = 2 }},
  silence_display = {offset={1950,610},{path="Display_200_50_1frames"}},
  
  glitch = {offset = { 2300,450 },{ path = "Knob_49_63frames", frames = 63 }},
  glitch_on = {offset = { 2560,395 },{ path = "Lamp_10_GREEN_2frames", frames = 2 }},
  glitch_display = {offset={2300,610},{path="Display_200_50_1frames"}},
  
}
back = {
  Bg = { {path = "back2U"} },
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





