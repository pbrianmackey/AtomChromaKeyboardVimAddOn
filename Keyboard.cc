void CustomLogic()
{
	std::cout << "Hello World!";
	CREATEKEYBOARDCUSTOMGRIDEFFECTS CreateKeyboardCustomGridEffects = (CREATEKEYBOARDCUSTOMGRIDEFFECTS)GetProcAddress(hModule, "CreateKeyboardCustomGridEffects");

	CUSTOM_GRID_EFFECT_TYPE Grid = {};

    // Presets
    Grid.Key[4][18] = RED;
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	Grid.Key[4][18] = RGB(r,g,b);

	int ROWS = 6;
	int COLUMNS = 22;
	for(int i = 0; i < ROWS; i++)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;


		for(int j = 0; j < COLUMNS; j++)
		{
			Grid.Key[i][j] = RGB(r,g,b);
		}

	}
	CreateKeyboardCustomGridEffects(Grid, nullptr);
