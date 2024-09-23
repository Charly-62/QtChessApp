# QtChessApp

**QtChessApp** is a C++ and Qt-based chess game that allows two players to compete over a network in real time. The project focuses on enforcing chess rules, efficient network communication, and an interactive GUI, making it ideal for studying networked game development.

## Features

### Chess Rules and Game Logic
- Full implementation of chess rules:
  - **Castling** (short and long)
  - **En Passant**
  - **Pawn Promotion** (Queen, Rook, Bishop, Knight)
  - **Pinning**
- Move validation via the `logik` class ensures all moves are legal before execution.
- **Turn Management**: Alternates turns and prevents illegal moves.
- **Piece Classes**: Each piece has its own class with specific movement rules, derived from the base `piece` class.
- **Undo Moves**: Undo moves is supported in both local and network mode. In network mode, undo requires the opponent’s acceptance.

### Graphical User Interface (GUI)
- Built with Qt widgets, providing a responsive chessboard display.
- **Key Features**:
  - Mouse-based move input with visual highlights for possible moves.
  - Real-time updates of the board state.
  - Integrated game controls for setting roles (Server/Client) and managing connections.
  - Timer, score tracking, and display of captured pieces.
- Managed by the `SchachApp` class.

### Networking
- **TCP/IP Protocol**: Reliable transmission of game data between clients.
- **Client/Server Architecture**:
  - One player acts as a server, and the other connects as a client.
  - The server initiates and broadcasts moves.
- Uses **QTcpSocket** and **QDataStream** for cross-platform, robust communication.
- **Reconnection Support**: Automatic client reconnection after unexpected disconnection.
- **Chat & Names**: In-game chat with built-in censorship for English and German swear words.
- **Safety**: Packet validation, buffering, controlled disconnections, and DoS protection.

### Custom TCP Protocol

A custom protocol handles move and game state transmission, serialized via `QDataStream`. The protocol ensures minimal yet comprehensive data transfer for each action.

#### Protocol Message Structure

| **Command**       | **Length (Bytes)** | **Data**                                                                                                                                             | **Direction**  |
|-------------------|--------------------|------------------------------------------------------------------------------------------------------------------------------------------------------|----------------|
| `0x01` - Game Start    | `0x02`                | `quint8`: Who starts (`0x00` - Server, `0x01` - Client) <br> `quint8`: Group number                                                                 | Server → Client |
| `0x02` - Response      | `0x01`                | `quint8`: Group number                                                                                                                               | Client → Server |
| `0x03` - Move          | `0x05`                | `quint8`: Start column <br> `quint8`: Start row <br> `quint8`: Target column <br> `quint8`: Target row <br> `quint8`: Move metadata (castling, etc.) | Bi-directional  |
| `0x04` - Move Response | `0x01`                | `quint8`: Move status (`0x00` - OK, `0x01` - Illegal move, `0x02` - Checkmate, etc.)                                                                 | Bi-directional  |

### Move Metadata Encoding

The `move metadata` byte is divided into two 4-bit nibbles:
- **MSN (Most Significant Nibble)**: Encodes special moves (e.g., pawn promotion).
- **LSN (Least Significant Nibble)**: Encodes move consequences (e.g., capture, checkmate, castling).

### Key Classes

1. **Game Logic**:
   - `game`: Manages the board, piece movement, and turn management.
   - `piece` and derived classes (e.g., `pawn`, `rook`, `knight`): Define specific movement rules for each piece.
   - `logik`: Validates the legality of moves before they are executed.

2. **Networking**:
   - `netzwerk`: Handles network connections and sends/receives moves.
   - **QTcpSocket** and **QDataStream**: Facilitate TCP communication and data transfer.

3. **GUI**:
   - `SchachApp`: Provides the interface for player interaction, game control, and visual display.
   - Built using `QWidget` and Qt’s event handling system.

### Memory Management
- Utilizes **smart pointers** (`std::unique_ptr`, `std::shared_ptr`) for automatic memory management and prevention of memory leaks.
- Memory issues were tracked and resolved using **Valgrind**.


## Build and Run with Automatically Generated Executables

Pre-built binaries for Windows, macOS, and Linux are available in the [latest release](https://github.com/Charly-62/QtChessApp/releases/latest).

### **Windows**

1. **Download** the latest Windows ZIP file from [here](https://github.com/Charly-62/QtChessApp/releases/latest/download/QtChessApp_Windows.zip).
2. **Extract** the contents of the ZIP file.
3. **Run** `schach.exe` to start the application.

### **macOS**

1. **Download** the latest macOS ZIP file from [here](https://github.com/Charly-62/QtChessApp/releases/latest/download/QtChessApp_macOS.zip).
2. **Open the app**:
   - **Right-click** (not left-click!) `Schach.app` and select **Open**.
   - If you see a message saying "the developer cannot be verified" click **Open** again to run the app. 

### **Linux**

1. **Download** the latest AppImage file from [here](https://github.com/Charly-62/QtChessApp/releases/latest/download/QtChessApp_Linux.AppImage).
2. **Make the AppImage executable**:

   ```bash
   chmod +x Schach-*.AppImage
   ```

3. **Run the AppImage**:

   ```bash
   ./Schach-*.AppImage
   ```


### **Note on Third-Party Antivirus Protection**

Some third-party antivirus programs (such as ESET) may flag or block `schach.exe` due to it being an unsigned executable. If you encounter issues running the application, you may need to temporarily disable protection or add `schach.exe` to ESET's exclusions. Windows Defender is not a problem, just some external protection programs.

If you still have concerns about the safety of the executable, you can:

- **Verify the Build Process:** The executable is generated using a public GitHub Actions workflow, which you can review in the [Actions tab](https://github.com/Charly-62/QtChessApp/actions) of this repository. This workflow runs the build process openly and securely.
  
- **Build the Program Yourself:** You can follow the steps in the next section to build the application from source using Qt. This ensures you have full control over the build process and can verify its integrity.


## Build and run from Source (Alternatively)

To build and run the project from source, ensure you have Qt5 (or higher) installed.

### **Build**

1. **Clone the repository**:

   ```bash
   git clone https://github.com/Charly-62/QtChessApp.git QtChessApp
   ```

2. **Open the project file `schach.pro` in Qt Creator and build the project.**

### **Alternatively, build from the command line:**

**Linux and macOS**:

   ```bash
   cd QtChessApp
   mkdir build
   cd build
   qmake ../schach/schach.pro
   make
   ./schach
   ```

**Windows**:

   ```bash
   cd QtChessApp
   mkdir build
   cd build
   qmake ..\schach\schach.pro
   nmake
   schach.exe
   ```

## Continuous Documentation

The project is documented with Doxygen, and documentation is automatically generated and published with every push using GitHub Actions and a CI Workflow. The latest documentation is available at: https://Charly-62.github.io/QtChessApp/.
