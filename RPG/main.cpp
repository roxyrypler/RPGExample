#include "raylib.h"

#include "game.h"
#include "loading.h"
#include "main.h"
#include "map.h"
#include "pause.h"
#include "resource_ids.h"
#include "screens.h"

// all the states the program can be in 
enum class ApplicationStates
{
	Startup,
	Loading,
	Menu,
	Running,
	Paused,
	Quiting
};

ApplicationStates ApplicationState = ApplicationStates::Startup;

// the main menu screen
class MainMenuScreen : public Screen
{
public:
	void Draw() override
	{
		// dim the background
		DimSceen();

		// title
		DrawCenteredText(40, "Raylib RPG Example", 40, BLUE);

		// version and copyright
		DrawText(VersionString, 2, GetScreenHeight() - 10, 10, GRAY);
		DrawText(CopyrightString, GetScreenWidth() - 2 - MeasureText(CopyrightString, 10), GetScreenHeight() - 10, 10, GRAY);

		// play button
		if (CenteredButton(GetScreenHeight() / 4, "Play"))
			StartGame();
		
		// options button
		CenteredButton(GetScreenHeight()/2, "Options");

		// quit button
		if (CenteredButton(GetScreenHeight() - (GetScreenHeight() / 4), "Quit"))
			QuitApplication();
	}
};

MainMenuScreen MainMenu;

// setup the window and icon
void SetupWindow()
{
	SetExitKey(0);
	SetTargetFPS(144);

	// load an image for the window icon
	Image icon = LoadImage("resources/icons/Icon.6_98.png");

	// ensure that the picture is in the correct format
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	// replace the background and border colors with transparent
	ImageColorReplace(&icon, BLACK, BLANK);
	ImageColorReplace(&icon, Color{ 136,136,136,255 }, BLANK);

	// set the icon
	SetWindowIcon(icon);

	// free the image data
	UnloadImage(icon);
}

void LoadComplete()
{
	ApplicationState = ApplicationStates::Menu;
	SetActiveScreen(&MainMenu);

	// load background world
	LoadMap("resources/maps/menu_map.tmx");
}

void GoToMainMenu()
{
	if (ApplicationState == ApplicationStates::Running || ApplicationState == ApplicationStates::Paused)
		QuitGame();

	LoadComplete();
}

void StartGame()
{
	ApplicationState = ApplicationStates::Running;
	SetActiveScreen(nullptr);
	InitGame();
}

void PauseGame()
{
	ApplicationState = ApplicationStates::Paused;
}

void ResumeGame()
{
	ApplicationState = ApplicationStates::Running;
	SetActiveScreen(nullptr);
	ActivateGame();
}

void EndGame()
{
	GoToMainMenu();
}

void QuitApplication()
{
	ApplicationState = ApplicationStates::Quiting;
}

void UpdateMainMenu()
{
	if (IsKeyPressed(KEY_ESCAPE))
		QuitApplication();
}

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1280,800,"RPG Example");
	SetupWindow();

	InitResources();

	ApplicationState = ApplicationStates::Loading;

	while (!WindowShouldClose() && ApplicationState != ApplicationStates::Quiting)
	{
		switch (ApplicationState)
		{
		case ApplicationStates::Loading:
			UpdateLoad();
			break;

		case ApplicationStates::Menu:
			UpdateMainMenu();
			break;

		case ApplicationStates::Running:
			UpdateGame();
			break;

		case ApplicationStates::Paused: 
			UpdatePaused();
			break;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawMap();

		DrawScreen();

		EndDrawing();
	}

	CleanupResources();
	CloseWindow();

	return 0;
}