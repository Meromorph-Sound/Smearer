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
  LIMITER_HARD_SOFT = 9,
  FILTER_MODE = 10,
  DURATION_MIN = 20,
  DURATION_RANGE = 21,
  WAVEFORM = 22,
  SILENCE = 23,
  SILENCE_ON = 24,
  JITTER = 25,
  JITTER_ON = 26,
  SMOOTHING = 27,
  PAN_CENTRE = 30,
  PAN_WIDTH = 31,
  RANDOMISE = 40,
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
  [9] = "limiter_hs",
  [10]= "filter_mode",
  [20]= "duration_min",
  [21]= "duration_range",
  [22]= "waveform",
  [23]= "silence",
  [25]= "jitter",
  [27]= "smoothing",
  [30]= "pan_centre",
  [31]= "pan_width",
  [40]= "randomise"
}

local MIDICC={
  [1] = 65,
  [2] = 66,
  [3] = 67,
  [4] = 68,
  [5] = 69,
  [6] = 70,
  [7] = 71,
  [8] = 72,
  [9] = 73,
  [10]= 74,
  [20]= 75,
  [21]= 76,
  [22]= 77,
  [23]= 78,
  [25]= 79,
  [27]= 80,
  [30]= 81,
  [31]= 82,
  [40]= 83
  }

local WindowNames= {
  [1] = 'rectangular',
  [2] = 'triangular',
  [3] = 'tanh',
  [4] = 'hanning',
  [5] = 'hamming',
  [6] = 'gaussian'
}
local WaveformNames= {
  [1] = 'sinusoid',
  [2] = 'triangle',
  [3] = 'square',
  [4] = 'sawtooth',
  [5] = 'random',
  [6] = 'exponential',
  [7] = 'step3',
  [8] = 'step4',
  [9] = 'stepupdown'
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

function samplesToTime(value,max)
  return (value/44.1)/max
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
		    default = 0,
		    ui_name = textFor(PropertyTags.SCALE_FACTOR),
		    ui_type = jbox.ui_linear {
          min=-3, 
          max=3, 
          units={{decimals=1,template = jbox.ui_text("scale" )}}
        }
      },
      ['pan_centre'] = jbox.number { 
        property_tag = PropertyTags.PAN_CENTRE,
		    default = 1,
		    ui_name = textFor(PropertyTags.PAN_CENTRE),
		    ui_type = jbox.ui_linear {
          min=0, 
          max=180, 
          units={{decimals=0,template = jbox.ui_text("degrees" )}}
        }
      },
      ['pan_width'] = jbox.number { 
        property_tag = PropertyTags.PAN_WIDTH,
		    default = 0,
		    ui_name = textFor(PropertyTags.PAN_WIDTH),
		    ui_type = jbox.ui_linear {
          min=-90, 
          max=90, 
          units={{decimals=0,template = jbox.ui_text("degrees" )}}
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
      ['filter_mode'] = jbox.number {
		    property_tag = PropertyTags.FILTER_MODE,
		    default = 0,
        steps = 2,
		    ui_name = textFor(PropertyTags.FILTER_MODE),
		    ui_type = jbox.ui_selector{ jbox.UI_TEXT_OFF, jbox.UI_TEXT_ON }
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
		    default = 0.25,
		    ui_name = textFor(PropertyTags.LIMITER),
		    ui_type = jbox.ui_linear {
          min=LIMITER_MIN, 
          max=LIMITER_MAX, 
          units={{decimals=1,template = jbox.ui_text("decibels" )}}
        }
      },
      ['duration_min'] = jbox.number {
        property_tag = PropertyTags.DURATION_MIN,
		    default = samplesToTime(597,1000),
		    ui_name = textFor(PropertyTags.DURATION_MIN),
        ui_type = jbox.ui_linear {
          min=1,
          max=1000,
          units={{decimals=0, template = jbox.ui_text("milliseconds")}}
        }
      },
      ['duration_range'] = jbox.number {
        property_tag = PropertyTags.DURATION_RANGE,
		    default = samplesToTime(20000,9000),
		    ui_name = textFor(PropertyTags.DURATION_RANGE),
        ui_type = jbox.ui_linear {
          min=0,
          max=9000,
          units={{decimals=0, template = jbox.ui_text("milliseconds")}}
        }
      },
      ['waveform'] = jbox.number {
        default=0,
        steps=9,
        ui_name = textFor(PropertyTags.WAVEFORM),  
        property_tag=PropertyTags.WAVEFORM,
        ui_type = jbox.ui_selector(apply(jbox.ui_text,WaveformNames))
      },
      ['silence'] = jbox.number {
        property_tag = PropertyTags.SILENCE,
		    default = 0,
		    ui_name = textFor(PropertyTags.SILENCE),
        ui_type = jbox.ui_linear {
          min=0,
          max=1,
          units={{decimals=2, template = jbox.ui_text("linear_template")}}
        }
      },
      ['jitter'] = jbox.number {
        property_tag = PropertyTags.JITTER,
		    default = 0,
		    ui_name = textFor(PropertyTags.JITTER),
        ui_type = jbox.ui_linear {
          min=0,
          max=1,
          units={{decimals=2, template = jbox.ui_text("linear_template")}}
        }
      },
      ['smoothing'] = jbox.number {
        property_tag = PropertyTags.SMOOTHING,
		    default = 1,
		    ui_name = textFor(PropertyTags.SMOOTHING),
        ui_type = jbox.ui_linear {
          min=1,
          max=250,
          units={{decimals=0, template = jbox.ui_text("linear_template")}}
        }
      },
      ['randomise'] = jbox.number {
		    property_tag = PropertyTags.RANDOMISE,
		    default = 0,
        steps = 2,
		    ui_name = textFor(PropertyTags.RANDOMISE),
		    ui_type = jbox.ui_selector{ jbox.UI_TEXT_OFF, jbox.UI_TEXT_ON }
      }
		}
	},
	rtc_owner = { properties = { 
      instance = jbox.native_object{} ,
  }},
	rt_owner = { properties = {
          silence_on = jbox.number {
            property_tag = PropertyTags.SILENCE_ON,
        default=0,
        steps=2,
        ui_name = textFor(PropertyTags.SILENCE),
        ui_type = jbox.ui_selector{ jbox.UI_TEXT_OFF, jbox.UI_TEXT_ON }
      },
      jitter_on = jbox.number {
            property_tag = PropertyTags.JITTER_ON,
        default=0,
        steps=2,
        ui_name = textFor(PropertyTags.JITTER),
        ui_type = jbox.ui_selector{ jbox.UI_TEXT_OFF, jbox.UI_TEXT_ON }
      }
      } }
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
  local cc = MIDICC[idx]
  midi_cc[cc] = fullProp
  remotes[fullProp] = remote_item(prop)
end

for k, v in pairs(midi_cc) do
  jbox.trace("MIDI "..k.." <-> "..v)
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







