#include "cub3d_bonus.h"
#include "parser_bonus.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(init_map, parser, .init = cr_redirect_stdout)
{
	struct s_tt
	{
		char  *name;
		char **av;
		int    expected;
	} tt[] = {
	    {"01) no player:", ft_split("./bin maps/invalid/no_player.cub", ' '), 0},
	    {"02) multiple players:", ft_split("./bin maps/invalid/multiple_players1.cub", ' '), 0},
	    {"03) multiple players:", ft_split("./bin maps/invalid/multiple_players2.cub", ' '), 0},
	    {"04) multiple players:", ft_split("./bin maps/invalid/multiple_players3.cub", ' '), 0},
	    {"05) multiple players:", ft_split("./bin maps/invalid/multiple_players4.cub", ' '), 0},
	    {"06) multiple players:", ft_split("./bin maps/invalid/multiple_players5.cub", ' '), 0},
	    {"07) multiple players:", ft_split("./bin maps/invalid/multiple_players6.cub", ' '), 0},
	    {"08) invalid map property:", ft_split("./bin maps/invalid/attr1.cub", ' '), 0},
	    {"09) invalid map property:", ft_split("./bin maps/invalid/attr2.cub", ' '), 0},
	    {"10) invalid map property:", ft_split("./bin maps/invalid/attr3.cub", ' '), 0},
	    {"11) invalid map property:", ft_split("./bin maps/invalid/attr4.cub", ' '), 0},
	    {"12) empty map:", ft_split("./bin maps/invalid/empty1.cub", ' '), 0},
	    {"13) empty map:", ft_split("./bin maps/invalid/empty2.cub", ' '), 0},
	    {"14) empty map:", ft_split("./bin maps/invalid/empty3.cub", ' '), 0},
	    {"15) empty map:", ft_split("./bin maps/invalid/empty4.cub", ' '), 0},
	    {"16) player at N:", ft_split("./bin maps/valid/sample.cub", ' '), 1},
	    {"17) player at S:", ft_split("./bin maps/valid/south.cub", ' '), 1},
	    {"18) player at W:", ft_split("./bin maps/valid/west.cub", ' '), 1},
	    {"19) player at E:", ft_split("./bin maps/valid/east.cub", ' '), 1},
	    {"20) minimum map size:", ft_split("./bin maps/valid/min_map.cub", ' '), 1},
	    {"21) exceeded maximum height:", ft_split("./bin maps/invalid/size_3_101.cub", ' '), 0},
	    {"22) exceeded maximum width:", ft_split("./bin maps/invalid/size_101_3.cub", ' '), 0},
	};
	size_t n = sizeof(tt) / sizeof(tt[0]);

	size_t i = -1;
	while (++i < n)
	{
		t_game game;

		game.map = NULL;
		game_init(&game);

		int got = init_map(&game, tt[i].av);
		cr_expect(got == tt[i].expected, "%s expect %d, but got %d", tt[i].name,
		          tt[i].expected, got);
		ft_free_matrix(tt[i].av);

		clean_params(&game.params);
		ft_free_matrix(game.map);
	}
}

Test(init_config_params, texture_parameters, .init = cr_redirect_stdout)
{
	struct s_tt
	{
		char  *name;
		char **av;
		int    expected;
	} tt[] = {
	    {"00) valid texture maps:", ft_split("./bin maps/valid/texture_params0.cub", ' '), 1},
	    {"01) valid texture maps:", ft_split("./bin maps/valid/texture_params1.cub", ' '), 1},
	    {"02) invalid texture file extension:", ft_split("./bin maps/invalid/texture_params2.cub", ' '), 0},
	    {"03) invalid texture file extension:", ft_split("./bin maps/invalid/texture_params3.cub", ' '), 0},
	    {"04) invalid texture file:", ft_split("./bin maps/invalid/texture_params4.cub", ' '), 0},
	    {"05) invalid texture file:", ft_split("./bin maps/invalid/texture_params5.cub", ' '), 0},
	    {"06) invalid identifier:", ft_split("./bin maps/invalid/texture_params6.cub", ' '), 0},
	    {"07) invalid identifier:", ft_split("./bin maps/invalid/texture_params7.cub", ' '), 0},
	    {"08) invalid identifier:", ft_split("./bin maps/invalid/texture_params8.cub", ' '), 0},
	    {"09) invalid identifier:", ft_split("./bin maps/invalid/texture_params9.cub", ' '), 0},
	    {"10) invalid identifier:", ft_split("./bin maps/invalid/texture_params10.cub", ' '), 0},
	    {"11) tab separated:", ft_split("./bin maps/valid/texture_params11.cub", ' '), 1},
	    {"12) tab and space separated:", ft_split("./bin maps/valid/texture_params12.cub", ' '), 1},
	    {"13) space and tab separated:", ft_split("./bin maps/valid/texture_params13.cub", ' '), 1},
	    {"14) duplicated texture:", ft_split("./bin maps/invalid/texture_params14.cub", ' '), 0},
	    {"15) duplicated texture:", ft_split("./bin maps/invalid/texture_params15.cub", ' '), 0},
	    {"16) empty lines between:", ft_split("./bin maps/valid/texture_params16.cub", ' '), 1},
	    {"17) empty lines between:", ft_split("./bin maps/valid/texture_params17.cub", ' '), 1},
	    {"18) empty lines between:", ft_split("./bin maps/valid/texture_params18.cub", ' '), 1},
	    {"19) empty lines between:", ft_split("./bin maps/valid/texture_params19.cub", ' '), 1},
	};
	size_t n = sizeof(tt) / sizeof(tt[0]);

	size_t i = -1;
	while (++i < n)
	{
		t_game game;

		game.map = NULL;
		game_init(&game);

		int got = init_config_params(&game, tt[i].av[1]);
		cr_expect(got == tt[i].expected, "%s expect %d, but got %d", tt[i].name,
		          tt[i].expected, got);
		ft_free_matrix(tt[i].av);

		clean_params(&game.params);
		ft_free_matrix(game.map);
	}
}

Test(init_config_params, color_parameters, .init = cr_redirect_stdout)
{
	struct s_tt
	{
		char  *name;
		char **av;
		int    expected;
	} tt[] = {
	    {"01) valid color separated by space:", ft_split("./bin maps/valid/color1.cub", ' '), 1},
	    {"02) valid color separated by tab:", ft_split("./bin maps/valid/color2.cub", ' '), 1},
	    {"03) valid color separated by multiple spaces/tabs:", ft_split("./bin maps/valid/color3.cub", ' '), 1},
	    {"04) valid color between empty lines:", ft_split("./bin maps/valid/color4.cub", ' '), 1},
	    {"05) invalid identifier:", ft_split("./bin maps/invalid/color5.cub", ' '), 0},
	    {"06) invalid identifier:", ft_split("./bin maps/invalid/color6.cub", ' '), 0},
	    {"07) invalid identifier:", ft_split("./bin maps/invalid/color7.cub", ' '), 0},
	    {"08) invalid identifier:", ft_split("./bin maps/invalid/color8.cub", ' '), 0},
	    {"09) missing color:", ft_split("./bin maps/invalid/color9.cub", ' '), 0},
	    {"10) missing color:", ft_split("./bin maps/invalid/color10.cub", ' '), 0},
	    {"11) missing color:", ft_split("./bin maps/invalid/color11.cub", ' '), 0},
	    {"12) missing color:", ft_split("./bin maps/invalid/color12.cub", ' '), 0},
	    {"13) missing color:", ft_split("./bin maps/invalid/color13.cub", ' '), 0},
	    {"14) missing color:", ft_split("./bin maps/invalid/color14.cub", ' '), 0},
	    {"15) missing color:", ft_split("./bin maps/invalid/color15.cub", ' '), 0},
	    {"16) missing color:", ft_split("./bin maps/invalid/color16.cub", ' '), 0},
	    {"17) missing color:", ft_split("./bin maps/invalid/color17.cub", ' '), 0},
	    {"18) missing color:", ft_split("./bin maps/invalid/color18.cub", ' '), 0},
	    {"19) not a number:", ft_split("./bin maps/invalid/color19.cub", ' '), 0},
	    {"20) not a number:", ft_split("./bin maps/invalid/color20.cub", ' '), 0},
	    {"21) not a number:", ft_split("./bin maps/invalid/color21.cub", ' '), 0},
	    {"22) not a number:", ft_split("./bin maps/invalid/color22.cub", ' '), 0},
	    {"23) out of range:", ft_split("./bin maps/invalid/color23.cub", ' '), 0},
	    {"24) out of range:", ft_split("./bin maps/invalid/color24.cub", ' '), 0},
	    {"25) out of range:", ft_split("./bin maps/invalid/color25.cub", ' '), 0},
	    {"26) out of range:", ft_split("./bin maps/invalid/color26.cub", ' '), 0},
	    {"27) out of range:", ft_split("./bin maps/invalid/color27.cub", ' '), 0},
	    {"28) out of range:", ft_split("./bin maps/invalid/color28.cub", ' '), 0},
	    {"29) missing property:", ft_split("./bin maps/invalid/color29.cub", ' '), 0},
	    {"30) missing property:", ft_split("./bin maps/invalid/color30.cub", ' '), 0},
	};
	size_t n = sizeof(tt) / sizeof(tt[0]);

	size_t i = -1;
	while (++i < n)
	{
		t_game game;

		game.map = NULL;
		game_init(&game);

		int got = init_config_params(&game, tt[i].av[1]);
		cr_expect(got == tt[i].expected, "%s expect %d, but got %d", tt[i].name,
		          tt[i].expected, got);
		ft_free_matrix(tt[i].av);

		clean_params(&game.params);
		ft_free_matrix(game.map);
	}
}

Test(init_map, map_borders, .init = cr_redirect_stdout)
{
	struct s_tt
	{
		char  *name;
		char **av;
		int    expected;
	} tt[] = {
	    {"01) invalid top border:", ft_split("./bin maps/border/borders1.cub", ' '), 0},
	    {"02) invalid top border:", ft_split("./bin maps/border/borders2.cub", ' '), 0},
	    {"03) invalid top border:", ft_split("./bin maps/border/borders3.cub", ' '), 0},
	    {"04) invalid top border:", ft_split("./bin maps/border/borders4.cub", ' '), 0},
	    {"05) invalid top border:", ft_split("./bin maps/border/borders5.cub", ' '), 0},
	    {"06) invalid top border:", ft_split("./bin maps/border/borders6.cub", ' '), 0},
	    {"07) invalid bottom border:", ft_split("./bin maps/border/borders7.cub", ' '), 0},
	    {"08) invalid bottom border:", ft_split("./bin maps/border/borders8.cub", ' '), 0},
	    {"09) invalid bottom border:", ft_split("./bin maps/border/borders9.cub", ' '), 0},
	    {"10) invalid bottom border:", ft_split("./bin maps/border/borders10.cub", ' '), 0},
	    {"11) invalid bottom border:", ft_split("./bin maps/border/borders11.cub", ' '), 0},
	    {"12) invalid bottom border:", ft_split("./bin maps/border/borders12.cub", ' '), 0},
	    {"13) invalid left border:", ft_split("./bin maps/border/borders13.cub", ' '), 0},
	    {"14) invalid left border:", ft_split("./bin maps/border/borders14.cub", ' '), 0},
	    {"15) invalid left border:", ft_split("./bin maps/border/borders15.cub", ' '), 0},
	    {"16) invalid left border:", ft_split("./bin maps/border/borders16.cub", ' '), 0},
	    {"17) invalid left border:", ft_split("./bin maps/border/borders17.cub", ' '), 0},
	    {"18) invalid left border:", ft_split("./bin maps/border/borders18.cub", ' '), 0},
	    {"19) valid with spaces:", ft_split("./bin maps/border/borders19.cub", ' '), 1},
	    {"20) invalid right border:", ft_split("./bin maps/border/borders20.cub", ' '), 0},
	    {"21) invalid right border:", ft_split("./bin maps/border/borders21.cub", ' '), 0},
	    {"22) invalid right border:", ft_split("./bin maps/border/borders22.cub", ' '), 0},
	    {"23) invalid right border:", ft_split("./bin maps/border/borders23.cub", ' '), 0},
	    {"24) invalid right border:", ft_split("./bin maps/border/borders24.cub", ' '), 0},
	    {"25) invalid right border:", ft_split("./bin maps/border/borders25.cub", ' '), 0},
	    {"26) valid with space in right side:", ft_split("./bin maps/border/borders26.cub", ' '), 1},
	    {"27) valid with tab on right side:", ft_split("./bin maps/border/borders27.cub", ' '), 1},
	    {"28) invalid right border:", ft_split("./bin maps/border/borders28.cub", ' '), 0},
	    {"29) valid:", ft_split("./bin maps/border/borders29.cub", ' '), 1},
	    {"30) valid with spaces:", ft_split("./bin maps/border/borders30.cub", ' '), 1},
	    {"31) valid with spaces:", ft_split("./bin maps/border/borders31.cub", ' '), 1},
	    {"32) invalid map structure:", ft_split("./bin maps/border/borders32.cub", ' '), 0},
	    {"33) invalid map structure:", ft_split("./bin maps/border/borders33.cub", ' '), 0},
	    {"34) invalid map structure:", ft_split("./bin maps/border/borders34.cub", ' '), 0},
	    {"35) invalid map structure:", ft_split("./bin maps/border/borders35.cub", ' '), 0},
	    {"36) invalid map structure:", ft_split("./bin maps/border/borders36.cub", ' '), 0},
	    {"37) valid map:", ft_split("./bin maps/border/borders37.cub", ' '), 1},
	    {"38) invalid border with player:", ft_split("./bin maps/border/borders38.cub", ' '), 0},
	    {"39) invalid border with player:", ft_split("./bin maps/border/borders39.cub", ' '), 0},
	    {"40) invalid border with player:", ft_split("./bin maps/border/borders40.cub", ' '), 0},
	    {"41) invalid border with player:", ft_split("./bin maps/border/borders41.cub", ' '), 0},
	    {"42) invalid border with player:", ft_split("./bin maps/border/borders42.cub", ' '), 0},
	    {"43) invalid border with player:", ft_split("./bin maps/border/borders43.cub", ' '), 0},
	    {"44) invalid border with player:", ft_split("./bin maps/border/borders44.cub", ' '), 0},
	    {"45) invalid border with player:", ft_split("./bin maps/border/borders45.cub", ' '), 0},
	    {"46) invalid player position:", ft_split("./bin maps/border/borders46.cub", ' '), 0},
	    {"47) invalid player position:", ft_split("./bin maps/border/borders47.cub", ' '), 0},
	    {"48) invalid player position:", ft_split("./bin maps/border/borders48.cub", ' '), 0},
	    {"49) invalid player position:", ft_split("./bin maps/border/borders49.cub", ' '), 0},
	    {"50) invalid border:", ft_split("./bin maps/border/borders50.cub", ' '), 0},
	    {"51) invalid border:", ft_split("./bin maps/border/borders51.cub", ' '), 0},
	    {"52) invalid border:", ft_split("./bin maps/border/borders52.cub", ' '), 0},
	    {"53) invalid border:", ft_split("./bin maps/border/borders53.cub", ' '), 0},
	    {"54) invalid border:", ft_split("./bin maps/border/borders54.cub", ' '), 0},
	    {"55) invalid border:", ft_split("./bin maps/border/borders55.cub", ' '), 0},
	    {"56) invalid border:", ft_split("./bin maps/border/borders56.cub", ' '), 0},
	    {"57) invalid border:", ft_split("./bin maps/border/borders57.cub", ' '), 0},
	    {"58) invalid border:", ft_split("./bin maps/border/borders58.cub", ' '), 0},
	    {"59) invalid border:", ft_split("./bin maps/border/borders59.cub", ' '), 0},
	    {"60) valid border:", ft_split("./bin maps/border/borders60.cub", ' '), 1},
	    {"61) valid border:", ft_split("./bin maps/border/borders61.cub", ' '), 1},
	    {"62) valid border:", ft_split("./bin maps/border/borders62.cub", ' '), 1},
	    {"63) valid border:", ft_split("./bin maps/border/borders63.cub", ' '), 1},
	    {"64) valid border:", ft_split("./bin maps/border/borders64.cub", ' '), 1},
	    {"65) valid border:", ft_split("./bin maps/border/borders65.cub", ' '), 1},
	    {"66) invalid border:", ft_split("./bin maps/border/borders66.cub", ' '), 0},
	    {"67) invalid border:", ft_split("./bin maps/border/borders67.cub", ' '), 0},
	    {"68) invalid border:", ft_split("./bin maps/border/borders68.cub", ' '), 0},
	    {"69) invalid border:", ft_split("./bin maps/border/borders69.cub", ' '), 0},
	    {"70) valid border:", ft_split("./bin maps/border/borders70.cub", ' '), 1},
	    {"71) invalid horizontal empty line:", ft_split("./bin maps/border/borders71.cub", ' '), 0},
	    {"72) invalid horizontal empty line:", ft_split("./bin maps/border/borders72.cub", ' '), 0},
	    {"73) invalid horizontal empty line:", ft_split("./bin maps/border/borders73.cub", ' '), 0},
	    {"74) valid map:", ft_split("./bin maps/border/borders74.cub", ' '), 1},
	    {"75) invalid horizontal empty line:", ft_split("./bin maps/border/borders75.cub", ' '), 0},
	    {"76) invalid horizontal empty line:", ft_split("./bin maps/border/borders76.cub", ' '), 0},
	    {"77) invalid horizontal empty line:", ft_split("./bin maps/border/borders77.cub", ' '), 0},
	    {"79) valid map:", ft_split("./bin maps/border/borders79.cub", ' '), 1},
	    {"80) valid map:", ft_split("./bin maps/border/borders80.cub", ' '), 1},
	    {"81) valid map:", ft_split("./bin maps/border/borders81.cub", ' '), 1},
	};
	size_t n = sizeof(tt) / sizeof(tt[0]);

	size_t i = -1;
	while (++i < n)
	{
		t_game game;

		game.map = NULL;
		game_init(&game);

		int got = init_map(&game, tt[i].av);
		cr_expect(got == tt[i].expected, "%s expect %d, but got %d", tt[i].name,
		          tt[i].expected, got);
		ft_free_matrix(tt[i].av);

		clean_params(&game.params);
		ft_free_matrix(game.map);
	}
}
