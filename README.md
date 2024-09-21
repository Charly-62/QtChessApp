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
| `0x04` - Move Response | `0x01`                | `quint8`: Move status (`0x00` - OK, `0x01` - Illegal move, `0x02` - Checkmate, etc.)                                                                 | Server → Client |

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

## Build and Run

To build and run the project, use **Qt Creator** with Qt5 installed:

1. Clone the repository:
   ```bash
   git clone https://github.com/Charly-62/QtChessApp.git QtChessApp

2. Open `schach.pro` in Qt Creator.

3. Build and run the project within Qt Creator.

## Continuous Documentation

The project is documented with Doxygen, and documentation is automatically generated and published with every push using GitHub Actions and a CI Workflow. The latest documentation is available at: https://Charly-62.github.io/QtChessApp/.