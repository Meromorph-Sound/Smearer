format_version = "2.0"

local LightBlue = {26,130,196}
local White = {255,255,255}

function simpleNode(name) 
  return { graphics = { node = name },value = "/custom_properties/"..name }
end

front = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.device_name { graphics = { node = "deviceName" } },
    jbox.sequence_fader{ 
      graphics = { node = "onoffbypass" },
      handle_size = 0,
      value = "/custom_properties/builtin_onoffbypass" 
    },
    jbox.patch_browse_group { graphics = {node="patches"}},
    jbox.patch_name{
      graphics = { node = "patch" },
      fg_color = { 255,255,255 },
      loader_alt_color = LightBlue,
      center = false,
      text_style = "Bold LCD font",
    },
    jbox.analog_knob { graphics = { node = "half_width" },value = "/custom_properties/half_width"},
    jbox.analog_knob {graphics = { node = "n_oscillators" },value = "/custom_properties/n_oscillators"},
    jbox.analog_knob (simpleNode("scale_factor")),
    jbox.up_down_button(simpleNode("window")),
    jbox.analog_knob({ graphics = { node = "window_display" },value = "/custom_properties/window" }),
    jbox.toggle_button(simpleNode("filter_on")),
    jbox.analog_knob (simpleNode("filter_q")),
    jbox.toggle_button(simpleNode("limiter_on")),
    jbox.analog_knob (simpleNode("limiter")),
    jbox.toggle_button(simpleNode("limiter_hs")),
    
  }
}
back = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.placeholder {graphics = { node = "Placeholder" }},
    jbox.audio_output_socket {graphics = { node = "audioOutputL" },socket = "/audio_outputs/Left"},
    jbox.audio_output_socket {graphics = { node = "audioOutputR" },socket = "/audio_outputs/Right"},
    jbox.audio_input_socket {graphics = { node = "audioInputL" },socket = "/audio_inputs/Left"},
    jbox.audio_input_socket {graphics = { node = "audioInputR" },socket = "/audio_inputs/Right"},
    jbox.device_name {graphics = { node = "deviceName" }}
  },
}
folded_front = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.device_name {graphics = { node = "deviceName" }},
    jbox.patch_name{
      graphics = { node = "patch" },
      fg_color = { 255,255,255 },
      loader_alt_color = LightBlue,
      center = false,
      text_style = "Bold LCD font",
    },
    },
}
folded_back = jbox.panel { 
  graphics = { node = "Bg" },
  cable_origin = { node = "CableOrigin" },
  widgets = {},
}
