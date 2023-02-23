#include "cub3d.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(init_map, parser, .init = cr_redirect_stdout)
{
	struct s_tt
	{
		char  *name;
		t_game game;
		char **av;
		int    expected;
	} tt[] = {
	    {"01) no player:", (t_game){}, ft_split("./bin maps/invalid/no_player.cub", ' '), 0},
	    {"02) multiple players:", (t_game){}, ft_split("./bin maps/invalid/multiple_players1.cub", ' '), 0},
	    {"03) multiple players:", (t_game){}, ft_split("./bin maps/invalid/multiple_players2.cub", ' '), 0},
	    {"04) multiple players:", (t_game){}, ft_split("./bin maps/invalid/multiple_players3.cub", ' '), 0},
	    {"05) multiple players:", (t_game){}, ft_split("./bin maps/invalid/multiple_players4.cub", ' '), 0},
	    {"06) multiple players:", (t_game){}, ft_split("./bin maps/invalid/multiple_players5.cub", ' '), 0},
	    {"07) multiple players:", (t_game){}, ft_split("./bin maps/invalid/multiple_players6.cub", ' '), 0},
	    {"08) invalid map property:", (t_game){}, ft_split("./bin maps/invalid/attr1.cub", ' '), 0},
	    {"09) invalid map property:", (t_game){}, ft_split("./bin maps/invalid/attr2.cub", ' '), 0},
	    {"10) invalid map property:", (t_game){}, ft_split("./bin maps/invalid/attr3.cub", ' '), 0},
	    {"11) invalid map property:", (t_game){}, ft_split("./bin maps/invalid/attr4.cub", ' '), 0},
	    {"12) empty map:", (t_game){}, ft_split("./bin maps/invalid/empty1.cub", ' '), 0},
	    {"13) empty map:", (t_game){}, ft_split("./bin maps/invalid/empty2.cub", ' '), 0},
	    {"14) empty map:", (t_game){}, ft_split("./bin maps/invalid/empty3.cub", ' '), 0},
	    {"15) empty map:", (t_game){}, ft_split("./bin maps/invalid/empty4.cub", ' '), 0},
	    {"16) player at N:", (t_game){}, ft_split("./bin maps/valid/sample.cub", ' '), 1},
	    {"17) player at S:", (t_game){}, ft_split("./bin maps/valid/south.cub", ' '), 1},
	    {"18) player at W:", (t_game){}, ft_split("./bin maps/valid/west.cub", ' '), 1},
	    {"19) player at E:", (t_game){}, ft_split("./bin maps/valid/east.cub", ' '), 1},
	    {"20) minimum map size:", (t_game){}, ft_split("./bin maps/valid/min_map.cub", ' '), 1},
	};
	size_t n = sizeof(tt) / sizeof(tt[0]);

	int i = -1;
	while (++i < n)
	{
		int got = init_map(&tt[i].game, tt[i].av);
		cr_expect(got == tt[i].expected, "%s expect %d, but got %d", tt[i].name,
		          tt[i].expected, got);
	}
}