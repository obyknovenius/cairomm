# data

# Input: install_prefix, install_libdir, install_datadir, install_includedir,
#        install_pkgconfigdir, cairomm_pcname, cairomm_api_version,
#        cairomm_requires
# Output: -

pkg_conf_data = configuration_data()
pkg_conf_data.set('prefix', install_prefix)
pkg_conf_data.set('exec_prefix', '${prefix}')
pkg_conf_data.set('libdir', '${exec_prefix}' / install_libdir)
pkg_conf_data.set('datarootdir', '${prefix}' / install_datadir)
pkg_conf_data.set('datadir', '${datarootdir}')
pkg_conf_data.set('includedir', '${prefix}' / install_includedir)
pkg_conf_data.set('PACKAGE_VERSION', meson.project_version())
pkg_conf_data.set('CAIROMM_MODULE_NAME', cairomm_pcname)
pkg_conf_data.set('CAIROMM_API_VERSION', cairomm_api_version)
pkg_conf_data.set('CAIROMM_MODULES', cairomm_requires)

configure_file(
  input: 'cairomm.pc.in',
  output: cairomm_pcname + '.pc',
  configuration: pkg_conf_data,
  install_dir: install_pkgconfigdir,
  install: true,
)

foreach cairomm_mod : ['ft', 'pdf', 'png', 'ps', 'quartz', 'quartz-font',
    'quartz-image', 'svg', 'win32', 'win32-font', 'xlib', 'xlib-xrender']

  # Install the module only if there is a corresponding cairo module.
  do_install = dependency('cairo-' + cairomm_mod, required: false).found()
  pc_file = 'cairomm-' + cairomm_mod
  configure_file(
    input: pc_file + '.pc.in',
    output: pc_file + '-' + cairomm_api_version + '.pc',
    configuration: pkg_conf_data,
    install_dir: install_pkgconfigdir,
    install: do_install,
  )
endforeach
