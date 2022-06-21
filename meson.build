project('nicobd', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules : ['DBus', 'Qml'])
bluezqt_dep = dependency('KF5BluezQt')

moc_files = qt5.compile_moc(headers : 'serialportprofile.h', dependencies: [qt5_dep, bluezqt_dep])

exe = executable('nicobd', 'nicobd.cpp', 'serialportprofile.cpp', moc_files,
  install : true, dependencies: [qt5_dep, bluezqt_dep])

test('basic', exe)
