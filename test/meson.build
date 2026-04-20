inc = include_directories('../include', '.')

tests = [['Conversions', 'conversions.c'],
         ['Fen', 'fen.c'],
         ['Moves', 'moves.c'],
         ['Attack Masks', 'attack_masks.c'],
         ['Magic', 'magic.c']]

foreach test:tests 
  e = executable(test[0], files(test[1]) + sources,
                include_directories : inc)
  test(test[0], e)
endforeach
