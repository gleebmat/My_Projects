import os
import sys
import json


def load_game_data():
    game_state = "game_state.json"
    game_config = "game_config.json"

    if not os.path.exists(game_state):
        print(
            f"[Python AI] Error: '{game_state}' not found. Did C++ write it successfully?"
        )
        sys.exit(1)
    if not os.path.exists(game_config):
        print(
            f"[Python AI] Error: '{game_config}' not found. Did C++ write it successfully?"
        )
        sys.exit(1)

    try:
        with open(game_config, "r") as f:
            game_config = json.load(f)
        with open(game_state, "r") as f:
            game_state = json.load(f)

        return game_config, game_state
    except Exception as e:
        print(f"[Python AI] Error reading JSON file: {e}")
        sys.exit(1)
