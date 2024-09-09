MRuby::Build.new do |conf|
  toolchain :visualcpp
  if ENV['OS'] != 'Windows_NT' then
    conf.cc.flags << %w|-fPIC| # needed for using bundled gems
  end


  conf.gembox 'default'
  conf.gem :core => 'mruby-bin-mrbc'
  conf.gem :core => 'mruby-bin-debugger'
  conf.gem :github => 'mattn/mruby-require'
  conf.enable_debug
  conf.enable_cxx_exception
  conf.enable_test

  # Add Windows Socket library
  conf.linker.libraries << 'ws2_32'
end

MRuby::CrossBuild.new('host-debug') do |conf|
  toolchain :visualcpp
  if ENV['OS'] != 'Windows_NT' then
    conf.cc.flags << %w|-fPIC| # needed for using bundled gems
  end
  conf.gembox 'default'
  conf.gem :core => 'mruby-bin-mrbc'
  conf.gem :core => 'mruby-bin-debugger'
  conf.gem :github => 'mattn/mruby-require'

  conf.enable_debug
  conf.enable_test

  conf.enable_cxx_exception

  # Add Windows Socket library
  conf.linker.libraries << 'ws2_32'
end
