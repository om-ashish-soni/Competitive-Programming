# Mo-Code Backend

## Overview

Mo-Code Backend is the server-side engine for managing AI code assistants. It provides endpoints for:
- Managing tasks
- Running code
- Debugging and version control

## Directory Structure

The project is organized as follows:
- **agent/**: Core logic and orchestration of tasks.
- **api/**: REST API server endpoints.
- **cmd/**: CLI commands.
- **context/**: Utilities and helpers for task context.
- **headless-twitter/** and **headless-twitter-2/**: Deprecated modules.
- **mocode/**: Entry point and main functionality.
- **provider/**: Supported AI provider integrations like OpenAI, Gemini, etc.
- **storage/**: Backend data handling.
- **tools/**: Generic tooling utilities.
- **tweet2/** and **twitter/**: Specific auxiliary tools for handling tweets/content.

## Get Started

### Prerequisites

1. Go version 1.24+. To install Go, follow the [official instructions](https://golang.org/doc/install).
2. Git for version control.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/mo-code.git
   cd mo-code/backend
   ```

2. Install dependencies:
   ```bash
   go mod tidy
   ```

### Running the Server

To start the API server:
```bash
cd cmd/mocode
go run main.go
```

API server runs on `http://localhost:8080` by default.

### Testing

To run all tests:
```bash
go test ./...
```

## Contributing

We welcome contributions! Please:
- Fork the repository.
- Create a branch for your feature/fix.
- Test your changes thoroughly.
- Submit a Pull Request.

For major changes, open an issue to discuss what you want to contribute.

## License

MIT License. See `LICENSE` for details.