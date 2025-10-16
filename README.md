# 🎮 Console Tetris Game

A classic Tetris game built in C++ that runs in the Windows console. Features colorful blocks, ghost pieces, scoring system, and smooth controls.

![Game Version](https://img.shields.io/badge/version-1.0-blue)
![Platform](https://img.shields.io/badge/platform-Windows-green)
![Language](https://img.shields.io/badge/language-C%2B%2B-red)

## 📸 Features

- 🎨 7 different Tetromino pieces with unique colors
- 👻 Ghost piece preview (shows where piece will land)
- 📊 Score and level progression system
- ⚡ Increasing speed as you level up
- ⏸️ Pause functionality
- 🎯 Smooth controls and rotation system

## 🎮 Controls

| Key | Action |
|-----|--------|
| **A** / **D** | Move piece left / right |
| **W** | Rotate piece |
| **S** | Soft drop (faster fall) |
| **Spacebar** | Hard drop (instant drop) |
| **P** | Pause game |
| **Q** | Quit game |

## 🚀 Quick Start (For Windows Users)

### Option 1: Run Pre-compiled Version (Easiest)
1. Download `tetris.exe` from the [Releases](https://github.com/yourusername/tetris-game/releases) section
2. Double-click `tetris.exe` to play!

### Option 2: Compile it Yourself

#### Method A: Using Visual Studio (Recommended)
1. Install [Visual Studio Community](https://visualstudio.microsoft.com/downloads/) (free)
   - During installation, select "Desktop development with C++"
2. Download `tetris.cpp` from this repository
3. Open Visual Studio and create a new "Console App" project
4. Replace the default code with the content from `tetris.cpp`
5. Press `Ctrl+F5` to compile and run

#### Method B: Using MinGW/G++
1. Install MinGW compiler:
   - Download from [MinGW-w64](https://www.mingw-w64.org/downloads/)
   - Or install via [Chocolatey](https://chocolatey.org/): `choco install mingw`
2. Open Command Prompt in the project folder
3. Compile: `g++ tetris.cpp -o tetris.exe`
4. Run: `tetris.exe`

#### Method C: Using Dev-C++
1. Download [Dev-C++](https://sourceforge.net/projects/orwelldevcpp/)
2. Open `tetris.cpp` in Dev-C++
3. Press `F11` to compile and run

#### Method D: Using Code::Blocks
1. Download [Code::Blocks](http://www.codeblocks.org/downloads) with MinGW
2. Create new console project
3. Replace main.cpp content with `tetris.cpp`
4. Build and Run (`F9`)

## 📁 Files in this Repository

```
tetris-game/
│
├── tetris.cpp          # Source code (single file)
├── tetris.exe          # Compiled executable for Windows
├── README.md           # This file
└── LICENSE            # MIT License
```

## 💻 System Requirements

- **Operating System**: Windows 7/8/10/11
- **RAM**: 50 MB (minimal)
- **Compiler** (if building from source): Any C++11 compatible compiler
- **Console**: Windows Command Prompt or Windows Terminal

## 🛠️ Building from Source

### Detailed Compilation Instructions

**Basic compilation:**
```bash
g++ tetris.cpp -o tetris.exe
```

**With optimizations:**
```bash
g++ -O2 tetris.cpp -o tetris.exe
```

**Static linking (no DLL dependencies):**
```bash
g++ -static tetris.cpp -o tetris_standalone.exe
```

**Debug build:**
```bash
g++ -g -Wall tetris.cpp -o tetris_debug.exe
```

## ⚠️ Troubleshooting

### "tetris.exe is not recognized as an internal or external command"
- Make sure you're in the correct directory
- Use `./tetris.exe` or full path

### "The code execution cannot proceed because VCRUNTIME140.dll was not found"
- Install [Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x64.exe)
- Or compile with static linking: `g++ -static tetris.cpp -o tetris.exe`

### Console window closes immediately
- Run from Command Prompt instead of double-clicking
- Or add to code: `system("pause");` before `return 0;`

### Colors not showing properly
- Use Windows Terminal for better color support
- Or run in Command Prompt (not PowerShell ISE)

## 🎯 Gameplay Tips

1. **Scoring System:**
   - Single line: 100 × level
   - Double line: 300 × level
   - Triple line: 500 × level
   - Tetris (4 lines): 800 × level
   - Soft drop: 1 point per cell
   - Hard drop: 2 points per cell

2. **Level Progression:**
   - Level increases every 10 lines
   - Game speeds up with each level

3. **Strategy:**
   - Keep the board flat
   - Save the I-piece for Tetris clears
   - Use the ghost piece to plan drops
   - Don't build too high in the center

## 🔧 For Developers

### Project Structure
The entire game is contained in a single `tetris.cpp` file for simplicity. Key components:

- **Tetris Class**: Main game logic
- **Piece Definitions**: 7 tetromino shapes with rotations
- **Game Loop**: Input handling, rendering, and updates
- **Console Management**: Windows-specific console manipulation

### Customization Ideas
- Change colors in `PIECE_COLORS` array
- Adjust game speed in `dropSpeed` variable
- Modify scoring system in `clearLines()` function
- Add new pieces by extending the `PIECES` array

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! Feel free to:
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 🌟 Acknowledgments

- Inspired by the original Tetris game by Alexey Pajitnov
- Built with C++ and Windows Console API
- ASCII art rendering for retro feel

## 📞 Contact

Your Name - [@yourusername](https://twitter.com/yourusername)

Project Link: [https://github.com/yourusername/tetris-game](https://github.com/yourusername/tetris-game)

---

**Enjoy the game! 🎮** If you found this helpful, please give it a ⭐ on GitHub!
