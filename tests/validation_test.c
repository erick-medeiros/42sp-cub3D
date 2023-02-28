#include "cub3d.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(input_validation, validation, .init = cr_redirect_stdout)
{
	struct s_tt
	{
		char  *name;
		int    ac;
		char **av;
		int    expected;
	} tt[] = {
	    {"01) player at N; sample 10x10 map:", 2, ft_split("./bin maps/valid/sample.cub", ' '), 1},
	    {"02) 42 map example:", 2, ft_split("./bin maps/valid/example42.cub", ' '), 1},
	    {"03) no map:", 1, ft_split("./bin", ' '), 0},
	    {"04) multiple maps:", 3, ft_split("./bin maps/valid/sample.cub maps/valid/sample.cub", ' '), 0},
	    {"05) invalid extension:", 2, ft_split("./bin maps/valid/sample.cut", ' '), 0},
	    {"06) invalid extension:", 2, ft_split("./bin maps/valid/sample.cb", ' '), 0},
	    {"07) invalid extension:", 2, ft_split("./bin maps/valid/sample.cube", ' '), 0},
	    {"08) no extension/invalid file:", 2, ft_split("./bin maps/valid/sample", ' '), 0},
	};

	size_t n = sizeof(tt) / sizeof(tt[0]);

	int i = -1;
	while (++i < n)
	{
		t_game game;

		game.map = NULL;
		game_init(&game);

		int got = input_validation(&game, tt[i].ac, tt[i].av);
		cr_expect(got == tt[i].expected, "%s expect %d, but got %d", tt[i].name,
		          tt[i].expected, got);
		ft_free_matrix(tt[i].av);
		clean_params(&game.params);
	}
}
