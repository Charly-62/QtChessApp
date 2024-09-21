# QtChessApp

**QtChessApp** is a network-based chess game built with C++ and Qt, allowing two players to compete in real-time over a network. The project emphasizes correct chess rule enforcement, efficient network communication, and a responsive GUI, making it both a practical and educational tool for studying networked game development.

## Features

### Chess Rules and Game Logic
- Full implementation of chess rules, including:
  - **Castling** (both short and long)
  - **En Passant**
  - **Pawn Promotion** (to Queen, Rook, Bishop, or Knight)
- Comprehensive move validation using the `logik` class, ensuring legality before applying moves.
- **Turn Management**: Alternates between players, tracking whose turn it is and preventing illegal moves.
- **Piece Classes**: Each piece type (Pawn, Rook, Knight, Bishop, Queen, King) has its own class derived from the base `piece` class, with specific movement rules.

### Graphical User Interface (GUI)
- Developed with Qt's widgets and layouts, allowing for a dynamic and interactive chessboard display.
- **Features**:
  - Visual representation of the chessboard and pieces.
  - **Move input** via mouse interaction, with highlighted possible moves.
  - Real-time game updates to reflect the current board state.
  - Easy connection to network functions for setting roles (Server/Client) and managing connections.
- The `SchachApp` class manages all interactions with the GUI.

### Networking
- **TCP/IP Protocol**: The game uses TCP for reliable transmission of game data between two clients.
- **Client/Server Architecture**: 
  - One player acts as the server, while the other connects as a client.
  - The server is responsible for initiating the game and broadcasting moves.
- **Qt’s QTcpSocket** and `QDataStream` are used to handle network communication, ensuring cross-platform compatibility and robust data handling.

### TCP Protocol

The game uses a custom protocol for transmitting moves and game state information. Each message is serialized using `QDataStream`, and the protocol ensures minimal but complete data transfer for each action.

#### Protocol Message Structure

| **Command**       | **Length (Bytes)** | **Data**                                                                                                                                             | **Direction**  |
|-------------------|--------------------|------------------------------------------------------------------------------------------------------------------------------------------------------|----------------|
| `0x01` - Game Start    | `0x02`                | `quint8`: Who starts (`0x00` - Server, `0x01` - Client) <br> `quint8`: Group number                                                                 | Server → Client |
| `0x02` - Response      | `0x01`                | `quint8`: Group number                                                                                                                               | Client → Server |
| `0x03` - Move          | `0x05`                | `quint8`: Start column <br> `quint8`: Start row <br> `quint8`: Target column <br> `quint8`: Target row <br> `quint8`: Move metadata (castling, etc.) | Bi-directional  |
| `0x04` - Move Response | `0x01`                | `quint8`: Move status (`0x00` - OK, `0x01` - Illegal move, `0x02` - Checkmate, etc.)                                                                 | Server → Client |

### Advanced Move Metadata Encoding

The `move metadata` byte is split into two 4-bit nibbles:
- **Most Significant Nibble (MSN)**: Encodes special moves such as pawn promotion.
  - `0x1`: Bishop promotion
  - `0x2`: Knight promotion
  - `0x3`: Rook promotion
  - `0x4`: Queen promotion
- **Least Significant Nibble (LSN)**: Encodes move consequences.
  - `0x0`: Regular move
  - `0x1`: Capture
  - `0x2`: Checkmate
  - `0x4`: Castling

### Key Classes and Responsibilities

1. **Game Logic**:
   - `game`: Handles the board, piece movement, and turn management.
   - `piece` and its derived classes (`pawn`, `rook`, `knight`, etc.): Define movement rules for each piece.
   - `logik`: Ensures moves are legal before they are executed.

2. **Networking**:
   - `netzwerk`: Manages all aspects of the network connection, including sending and receiving moves.
   - `QTcpSocket` and `QDataStream`: Facilitate the TCP connection and serial data transfer.
   
3. **GUI**:
   - `SchachApp`: Provides the chessboard interface and manages player interaction with the game.
   - Uses `QWidget` and related Qt classes for layout and event handling.

### Memory Management
- The project uses **smart pointers** (`std::unique_ptr`, `std::shared_ptr`) where appropriate, minimizing memory leaks and ensuring safe object ownership.
- **Valgrind** has been used for leak detection during development.

## Build and Run

This project is developed using **Qt Creator** and requires Qt5 for building and running. To set up the project:

1. Clone the repository:
   ```bash
   git clone https://github.com/Charly-62/QtChessApp.git
   cd QtChessApp

2. Open 'schach.pro' in Qt Creator.

3. Build and run the project from Qt Creator.

## Continuous Documentation

The project is documented using Doxygen, and documentation is automatically generated and published with each push. You can access the latest documentation at: https://Charly-62.github.io/QtChessApp/.