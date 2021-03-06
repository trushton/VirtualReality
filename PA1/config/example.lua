sim_window = {
  view = {
    simulator_view = true;
  };
--fullscreen = true;
};

sim_window = {
  view = {
    simulator_view = true;
  };
--fullscreen = true;
};

perspective_window = {
  view = {
    eyes = {
      eye = cavr.sixdof("vrpn[ShortGlasses[0]]");
      -- left_eye = cavr.sixdof("emulated3");
      -- right_eye = cavr.sixdof("emulated2");
      -- stereo ="mono";
    };
    lower_left = cavr.sixdof("vrpn[ShortGlasses[0]]") * cavr.translate(-1, -1, -1);
    lower_right = cavr.sixdof("vrpn[ShortGlasses[0]]") * cavr.translate(1, -1, -1);
    upper_left = cavr.sixdof("vrpn[ShortGlasses[0]]") * cavr.translate(-1, 1, -1);
  };
  fullscreen = true;
};

perspective_window2 = {
  view = {
    eyes = {
      eye = cavr.sixdof("vrpn[ShortGlasses[0]]");
      -- left_eye = cavr.sixdof("emulated3");
      -- right_eye = cavr.sixdof("emulated2");
      -- stereo ="mono";
    };
    lower_left = cavr.sixdof("vrpn[ShortGlasses[0]]") * cavr.translate(1, -1, 1);
    lower_right = cavr.sixdof("vrpn[ShortGlasses[0]]") * cavr.translate(-1, -1, 1);
    upper_left = cavr.sixdof("vrpn[ShortGlasses[0]]") * cavr.translate(1, 1, 1);
  };
  fullscreen = true;
};

x11_renderer = {
  type = "x11gl";
  display = ":0.0";
  windows = {
    sim_window = sim_window;
    --sim_window2 = sim_window;
    perspective_window = perspective_window;
  };
};

x11_renderer2 = {
  type = "x11gl";
  display = ":0.1";
  windows = {
    --sim_window = sim_window;
    --sim_window2 = sim_window;
    perspective_window = perspective_window;

  };
};

x11_renderer3 = {
  type = "x11gl";
  display = ":0.2";
  windows = {
    --sim_window = sim_window;
    --sim_window2 = sim_window;
    perspective_window = perspective_window;
  };
};

x11_renderer4 = {
  type = "x11gl";
  display = ":0.0";
  windows = {
    --sim_window = sim_window;
    --sim_window2 = sim_window;
    perspective_window = perspective_window2;
  };
};

vrpn = {
  type = "vrpn";
  input_name = "vrpn";
  buttons = {
    "WiiMote0@projector.cse.unr.edu";
  };
  analogs = {
    "WiiMote0@projector.cse.unr.edu"
  };
  sixdofs = {
    "WiiMote0@tracker.rd.unr.edu:1";
    "ShortGlasses@tracker.rd.unr.edu:1";
  };
};

self = {
  hostname = "hpcvis7";
  ssh = "hpcvis7.cse.unr.edu";--"chase@" .. HOSTNAME;
  address = "hpcvis7.cse.unr.edu";
  plugins = {
    x11_renderer = x11_renderer;
    --x11_renderer2 = x11_renderer2;
    --x11_renderer3 = x11_renderer3;
    vrpn = vrpn;
  };
};


others = {
  hostname = "hpcvis9";
  ssh = "hpcvis9.cse.unr.edu";
  address = "hpcvis9.cse.unr.edu";--"tcp://" .. "hpcvis7" .. ":8888";
  plugins = {
    x11_renderer = x11_renderer4;
    vrpn = vrpn;
  };
};

others2 = {
  hostname = "hpcvis2";
  ssh = "hpcvis2";
  address = "hpcvis2";--"tcp://" .. "hpcvis7" .. ":8888";
  plugins = {
    x11_renderer = x11_renderer;
    vrpn = vrpn;
  };
};


machines = {
  self=self;
  --others;
  --self3 = others2;
};
