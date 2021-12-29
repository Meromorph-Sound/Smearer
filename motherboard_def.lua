format_version = "3.0"


local MAX_PHASE = math.pi
local LIMITER_MIN = -12
local LIMITER_MAX = 0

local PropertyTags = {
  HALF_WIDTH = 1,
  N_OSCILLATORS = 2,
  SCALE_FACTOR = 3,
  WINDOW = 4,
  FILTER_ON = 5,
  FILTER_Q = 6,
  LIMITER_ON = 7,
  LIMITER = 8,
  LIMITER_HARD_SOFT = 9
}

local PropertyNames= {
  [1] = "half_width",
  [2] = "n_oscillators",
  [3] = "scale_factor",
  [4] = "window",
  [5] = "filter_on",
  [6] = "filter_q",
  [7] = "limiter_on",
  [8] = "limiter",
  [9] = "limiter_hs"
}

local WindowNames= {
  [1] = 'rectangular',
  [2] = 'triangular',
  [3] = 'tanh',
  [4] = 'hanning',
  [5] = 'hamming',
  [6] = 'gaussian'
}

function  apply(fn,list)
  local out={}
  for idx,value in pairs(list) do
    out[idx]=fn(value)
  end
  return out
end

  

function textFor(n) 
  return jbox.ui_text(PropertyNames[n])
  end

function linearType()
  return jbox.ui_linear {
    min=0,
    max=1,
    units = {
      min_text = jbox.ui_text("zero"),
      max_text = jbox.ui_text("one"),
      { 
        decimals=2,
        unit = { template = jbox.ui_text("linear_template") }
      }
    }
  }
end

custom_properties = jbox.property_set{
	document_owner = {
		properties = {
		  ['half_width'] = jbox.number {
		    property_tag = PropertyTags.HALF_WIDTH,
		    default = 0,
        min=0,
        max=1,
		    ui_name = textFor(PropertyTags.HALF_WIDTH),
		    ui_type = jbox.ui_linear {
          min=1, 
          max=500, 
          units={{decimals=2,template = jbox.ui_text("hertz" )}}
        }
		  },
      ['n_oscillators']= jbox.number {
        property_tag = PropertyTags.N_OSCILLATORS,
        min=0,
        default = 1,
        steps=201,
        ui_name = textFor(PropertyTags.N_OSCILLATORS),
        ui_type = jbox.ui_linear {
          min=0, 
          max=200, 
          units={{decimals=0,template = jbox.ui_text("osc" )}}
        }
      },
		  ['scale_factor'] = jbox.number {
		    property_tag = PropertyTags.SCALE_FACTOR,
		    default = 0.5,
		    ui_name = textFor(PropertyTags.SCALE_FACTOR),
		    ui_type = jbox.ui_linear {
          min=0, 
          max=2, 
          units={{decimals=1,template = jbox.ui_text("scale" )}}
        }
      },
      ['window'] = jbox.number {
        default=0,
        steps=6,
        ui_name = textFor(PropertyTags.WINDOW),  
        property_tag=PropertyTags.WINDOW,
        ui_type = jbox.ui_selector(apply(jbox.ui_text,WindowNames))
      },
      ['filter_on'] = jbox.number {
		    property_tag = PropertyTags.FILTER_ON,
		    default = 0,
        steps = 2,
		    ui_name = textFor(PropertyTags.FILTER_ON),
		    ui_type = jbox.ui_selector{ jbox.UI_TEXT_OFF, jbox.UI_TEXT_ON }
      },
      ['filter_q'] = jbox.number {
		    property_tag = PropertyTags.FILTER_Q,
		    default = 0.5,
		    ui_name = textFor(PropertyTags.FILTER_Q),
		    ui_type = jbox.ui_linear {
          min=0, 
          max=1, 
          units={{decimals=3,template = jbox.ui_text("scale" )}}
        }
      },
      ['limiter_on'] = jbox.number {
		    property_tag = PropertyTags.LIMITER_ON,
		    default = 0,
        steps = 2,
		    ui_name = textFor(PropertyTags.LIMITER_ON),
		    ui_type = jbox.ui_selector{ jbox.UI_TEXT_OFF, jbox.UI_TEXT_ON }
      },
      ['limiter_hs'] = jbox.number {
		    property_tag = PropertyTags.LIMITER_HARD_SOFT,
		    default = 0,
        steps = 2,
		    ui_name = textFor(PropertyTags.LIMITER_HARD_SOFT),
		    ui_type = jbox.ui_selector{ jbox.UI_TEXT_OFF, jbox.UI_TEXT_ON }
      },
      ['limiter'] = jbox.number {
		    property_tag = PropertyTags.LIMITER,
		    default = 0,
		    ui_name = textFor(PropertyTags.LIMITER),
		    ui_type = jbox.ui_linear {
          min=LIMITER_MIN, 
          max=LIMITER_MAX, 
          units={{decimals=1,template = jbox.ui_text("decibels" )}}
        }
      }
		}
	},
	rtc_owner = { properties = { instance = jbox.native_object{} }},
	rt_owner = { properties = {} }
}

ui_groups = {}

audio_inputs = {
  Left = jbox.audio_input{ ui_name = jbox.ui_text("audioInputL") },
  Right = jbox.audio_input{ ui_name = jbox.ui_text("audioInputR") },
}
audio_outputs = {
  Left = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputL") },
  Right = jbox.audio_output{ ui_name = jbox.ui_text("audioOutputR") },
}





function remote_item(name)
  return {
    internal_name = name,
    short_ui_name = jbox.ui_text("short_"..name),
    shortest_ui_name = jbox.ui_text("shortest_"..name)
  }
end

local midi_cc = {}
local remotes = {}

for idx, prop in pairs(PropertyNames) do
  local fullProp = "/custom_properties/"..prop
  midi_cc[19+idx] = fullProp
  remotes[fullProp] = remote_item(prop)
end

midi_implementation_chart = { midi_cc_chart = midi_cc }
remote_implementation_chart = remotes



jbox.add_stereo_effect_routing_hint{
  left_input = "/audio_inputs/Left",
  right_input = "/audio_inputs/Right",
  left_output = "/audio_outputs/Left",
  right_output = "/audio_outputs/Right",
  type = "true_stereo"
}
jbox.add_stereo_audio_routing_target{
  signal_type = "return",
  left = "/audio_inputs/Left",
  right = "/audio_inputs/Right",
  auto_route_enable = true
}
jbox.add_stereo_audio_routing_target{
  signal_type = "send",
  left = "/audio_outputs/Left",
  right = "/audio_outputs/Right",
  auto_route_enable = true
}
jbox.add_stereo_audio_routing_pair{
  left = "/audio_inputs/Left",
  right = "/audio_inputs/Right"
}
jbox.add_stereo_audio_routing_pair{
  left = "/audio_outputs/Left",
  right = "/audio_outputs/Right"
}
jbox.set_effect_auto_bypass_routing{
  {
    "/audio_inputs/Left",
    "/audio_outputs/Left"
  },
  {
    "/audio_inputs/Right",
    "/audio_outputs/Right"
  }
}







