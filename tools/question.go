package tools

import (
	"context"
	"encoding/json"
	"fmt"
)

// Question allows the agent to ask the user a clarifying question.
// The result is returned via the event stream to the Flutter UI,
// which can display it as a prompt. The user's answer comes back
// as a new user message.
type Question struct{}

func NewQuestion() *Question { return &Question{} }

func (q *Question) Name() string { return "ask_user" }

func (q *Question) Description() string {
	return "Ask the user a clarifying question when you need more information to proceed. " +
		"Use this when the request is ambiguous or you need the user to make a choice. " +
		"Do NOT use this for rhetorical questions or to confirm actions you can figure out yourself."
}

func (q *Question) Parameters() string {
	return `{
		"type": "object",
		"properties": {
			"question": {
				"type": "string",
				"description": "The question to ask the user"
			},
			"options": {
				"type": "array",
				"items": {"type": "string"},
				"description": "Optional list of suggested answers for the user to choose from"
			}
		},
		"required": ["question"]
	}`
}

func (q *Question) Execute(ctx context.Context, argsJSON string) Result {
	var args struct {
		Question string   `json:"question"`
		Options  []string `json:"options"`
	}
	if err := json.Unmarshal([]byte(argsJSON), &args); err != nil {
		return Result{Error: fmt.Sprintf("invalid arguments: %v", err), Output: fmt.Sprintf("Error: invalid arguments: %v", err)}
	}

	// The question is returned as the tool result. The engine's event stream
	// will deliver it to the UI, which shows it to the user. The user's
	// response comes back as the next user message in the conversation.
	output := args.Question
	if len(args.Options) > 0 {
		output += "\n\nOptions:"
		for i, opt := range args.Options {
			output += fmt.Sprintf("\n  %d. %s", i+1, opt)
		}
	}

	return Result{
		Title:  "Question for user",
		Output: output,
		Metadata: map[string]any{
			"question": args.Question,
			"options":  args.Options,
		},
	}
}
