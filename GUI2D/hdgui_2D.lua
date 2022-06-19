format_version = "2.0"

local LightBlue = {26,130,196}
local White = {255,255,255}
local Yellow = {255,255,0}

function prop(name)
  return "/custom_properties/"..name
end

function simpleNode(name) 
  return { graphics = { node = name },value = prop(name) }
end

front = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.device_name { graphics = { node = "deviceName" } },
    jbox.sequence_fader{ 
      graphics = { node = "onoffbypass" },
      handle_size = 0,
      value = prop("builtin_onoffbypass") 
    },
    jbox.patch_browse_group { graphics = {node="patches"}},
    jbox.patch_name{
      graphics = { node = "patch" },
      fg_color = { 255,255,255 },
      loader_alt_color = LightBlue,
      center = false,
      text_style = "Bold LCD font",
    },
    jbox.analog_knob (simpleNode("half_width" )),
    jbox.analog_knob (simpleNode("n_oscillators")),
    jbox.analog_knob (simpleNode("scale_factor")),
    
    jbox.up_down_button(simpleNode("window")),
    jbox.analog_knob({ graphics = { node = "window_display" },value = prop("window") }),
    jbox.toggle_button(simpleNode("filter_on")),
    jbox.analog_knob (simpleNode("filter_q")),
    jbox.radio_button { graphics = { node = "filter_1" },value = prop("filter_mode"),index = 0},
    jbox.radio_button { graphics = { node = "filter_2" },value = prop("filter_mode"),index = 1},
    jbox.toggle_button(simpleNode("limiter_on")),
    jbox.analog_knob (simpleNode("limiter")),
    jbox.toggle_button(simpleNode("limiter_hs")),
    
    jbox.analog_knob (simpleNode('duration_min')),
    jbox.analog_knob (simpleNode('duration_range')),
    jbox.value_display { 
      graphics = { node = "duration_min_display" },
      value = prop("duration_min"),
      text_color = {255,255,0},
      text_style = "Small label font",
      horizontal_justification = "right",
      tooltip_template = jbox.ui_text("milliseconds")
    },
    jbox.value_display { 
      graphics = { node = "duration_range_display" },
      value = prop("duration_range"),
      text_color = {255,255,0},
      text_style = "Small label font",
      horizontal_justification = "right",
      tooltip_template = jbox.ui_text("milliseconds")
    },
    jbox.up_down_button(simpleNode("waveform")),
    jbox.analog_knob({ graphics = { node = "waveform_display" },value = prop("waveform") }),
    jbox.analog_knob(simpleNode('silence')),
    jbox.sequence_meter{ graphics = { node="silence_on" }, value=prop("silence_on")},
    jbox.value_display { 
      graphics = { node = "silence_display" },
      value = prop("silence"),
      text_color = {255,255,0},
      text_style = "Small label font",
      horizontal_justification = "right",
      tooltip_template = jbox.ui_text("scale")
    },
    jbox.analog_knob(simpleNode('jitter')),
    jbox.sequence_meter{ graphics = { node="jitter_on" }, value=prop("jitter_on")},
    jbox.value_display { 
      graphics = { node = "jitter_display" },
      value = prop("jitter"),
      text_color = {255,255,0},
      text_style = "Small label font",
      horizontal_justification = "right",
      tooltip_template = jbox.ui_text("scale")
    },
    --jbox.analog_knob(simpleNode('mix_ex')),
    --jbox.analog_knob(simpleNode('mix_in')),
    jbox.analog_knob(simpleNode('pan_centre')),
    jbox.analog_knob(simpleNode('pan_width')),
    
    jbox.momentary_button(simpleNode("randomise")),
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
    --jbox.momentary_button(simpleNode("randomise")),
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
