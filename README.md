# Minesweeper Game Project

## Overview

This project implements a 3D Minesweeper game using Unreal Engine. The game replicates the classic Minesweeper mechanics, allowing players to reveal cells, avoid bombs, and use strategies to clear the grid.

## Classes

### AMineSweeperPlayerController

The `AMineSweeperPlayerController` class handles player input and interactions. It detects mouse clicks and hover events to interact with the game grid.

#### Key Properties
- **LastHoveredCell**: The last cell that was hovered over by the mouse.
- **bCanClick**: Determines if the player can click (used for click cooldown).
- **ClickCooldown**: The time in seconds before another click is allowed.
- **LastClickTime**: The last recorded time of a click.

#### Key Methods
- `PlayerTick(float DeltaTime)`: Updates the player's actions every frame.
- `CheckHover()`: Checks if the mouse is hovering over a new cell.
- `OnLeftMouseClick()`: Handles left mouse click events.

### AMinesweeperGrid

The `AMinesweeperGrid` class manages the game grid, initializing cells, placing bombs, and handling game logic.

#### Key Properties
- **Rows**: Number of rows in the grid.
- **Columns**: Number of columns in the grid.
- **CellSize**: Size of each cell.
- **Cell**: The class type of the grid cells.
- **TotalBombs**: Total number of bombs in the grid.
- **GridArray**: 2D array of grid cells.

#### Key Methods
- `InitializeGrid()`: Initializes the grid with cells and places bombs.
- `LineTraceRevealCell(const FVector& Start, const FVector& End)`: Reveals the cell hit by a line trace.
- `CreateCell(int32 Row, int32 Column)`: Creates a cell at the specified grid coordinates.
- `GameOver()`: Handles the game over state.

### AGridCell

The `AGridCell` class represents individual cells in the Minesweeper grid, handling states such as being revealed, hovered, and bomb presence.

#### Key Properties
- **StaticMeshComponent**: The visual representation of the cell.
- **MineText**: Text component for displaying bomb count.
- **RevealedCell**: Material for revealed cells.
- **HoveredCell**: Material for hovered cells.
- **DefaultCell**: Material for default cells.
- **I, J**: Grid coordinates of the cell.
- **NeighborCount**: Number of neighboring bombs.
- **bIsBomb**: Indicates if the cell contains a bomb.
- **bIsRevealed**: Indicates if the cell is revealed.

#### Key Methods
- `OnHoverStart()`: Handles cell hover start events.
- `OnHoverEnd()`: Handles cell hover end events.
- `Reveal()`: Reveals the cell.
- `FloodFill()`: Reveals adjacent cells if no bombs are nearby.
- `CountBombs()`: Counts neighboring bombs.

## Features

- **Interactive Grid**: Players can reveal cells and mark bombs.
- **Hover Effects**: Visual feedback when hovering over cells.
- **Game Logic**: Handles bomb placement, cell revealing, and game over conditions.
- **Dynamic Grid**: Configurable grid size and bomb count.

## Development Process

1. **Player Controller**: Implement input handling and interaction logic.
2. **Grid Initialization**: Create and initialize the game grid with cells and bombs.
3. **Cell Interaction**: Develop cell hover and click functionalities.
4. **Game Logic**: Implement game state management, including win/lose conditions.
5. **Visual Feedback**: Add visual effects for cell states (hovered, revealed, bomb).

## Credits

This project is developed by Khaled Elsayed Zakaria.

![image](https://github.com/user-attachments/assets/95a4f8dc-d422-46e5-8883-2e280fbc1d74)
![image](https://github.com/user-attachments/assets/38abc8e5-7f31-4f29-b86d-525df52d94fe)
![image](https://github.com/user-attachments/assets/88507acb-04c8-4cfc-8be9-a5da52824ffe)
![image](https://github.com/user-attachments/assets/af02021e-e3d0-4d67-a39a-159471ae697a)



