project('chess', 'c',
  version : '0.1.0',
  license : 'MIT')

PCG_USE_INLINE_ASM=true

subdir('src')
subdir('test')

inc = include_directories('include')
executable('chess', files('src/main.c') + sources, include_directories : inc)
