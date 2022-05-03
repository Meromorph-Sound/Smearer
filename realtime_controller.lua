format_version = "1.0"

rtc_bindings = { 
  { source = "/environment/system_sample_rate", dest = "/global_rtc/init_instance" },
  { source = "/environment/instance_id", dest = "/global_rtc/init_instance" }
}

global_rtc = { 

  init_instance = function(source_property_path, instance_id)
    local new_no = jbox.make_native_object_rw("Instance", {instance_id})
    jbox.store_property("/custom_properties/instance", new_no);
  end,
}

sample_rate_setup = { 
native = {
    22050,
    44100,
    48000,
    88200,
    96000,
    192000
  },
}

rt_input_setup = { 
  notify = {
  "/custom_properties/builtin_onoffbypass",
  "/custom_properties/half_width",
  "/custom_properties/n_oscillators",
  "/custom_properties/scale_factor",
  "/custom_properties/limiter_on",
  "/custom_properties/limiter_hs",
  "/custom_properties/limiter",
   "/custom_properties/filter_on",
   "/custom_properties/filter_q",
   "/custom_properties/filter_mode",
   "/custom_properties/window",
   "/custom_properties/duration_min",
   "/custom_properties/duration_range",
   "/custom_properties/waveform",
   "/custom_properties/silence",
   "/custom_properties/jitter",
   "/custom_properties/smoothing",
--   "/custom_properties/mix_ex",
--   "/custom_properties/mix_in",
   "/custom_properties/mix_pr",
   "/custom_properties/randomise",
--  "/custom_properties/inGain",
--   "/custom_properties/outGain",
  "/audio_inputs/Left/connected",
  "/audio_inputs/Right/connected",
  "/audio_outputs/Left/connected",
  "/audio_outputs/Right/connected",
  "/transport/request_reset_audio",
  "/environment/master_tune",
  "/environment/system_sample_rate"
  }
}