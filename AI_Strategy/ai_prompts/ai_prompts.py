prompts_for_initial_start = """f"\nYou are a calculating tactical AI
playing a 2D grid combat game\n"
        "--- BATTLEFIELD RULES ---
        \n"
        "- You can only command a unit if its property can_act is true/.\n"
        "- Do not move onto any coordinate
        currently occupied by another unit (allies or enemies) and dont move outside the map boundaries.
        Your final and only goal is to win the game, by killing the units of the other player/players.
        You can implement different tactics to reach the goal\n\n"
        """
prompts_before_parsing = """\n1. Select ONE of your units where 'can_act is true for EACH turn(they cannot be the same in 1 turn\n
     When you decide to move, then give your answer in this format(this is just an example):
      unit_index: 2 (index of your chosen unit),
      action_type: 'move' (in this example I am showing moving),
      dx: 3 (your relative transfer on X-axis),
      dy: 2 (your relative transfer on Y-axis),

      BUT if you want to attack, thats the example for such a case:
      unit_index: 4 (index of your chosen unit),
      action_type: 'attack' (since you want to attack),
      target_index: 5 (the index of the enemy's unit you want to attack\n
      "You must return exactly 2 actions in the 'actions' list. You can choose any combination of Move or Attack for these 2 actions.    \n"""
important_prompt_before_parsing = """\n
        if you decide to move, you will give the relative displacement (dx, dy) for the unit you want to move.
        In this case (!!!) check if max(abs(dx), abs(dy)) <= unit's max_move, you can find max_moves for each unit in the prompts.
      If you decide to attack, check two-three times if your target is still in range before committing to the action.
      Always consider the availability of attackable targets to your units before deciding to attacks\n
      Play can play agressively, not hesitating when there is an option to attack twice. Throughout the game, you may need to fly away from the enemy units to avoid getting killed, simply what you want. 
      Always give the reasoning for your actions before submitting them
        - Movement: You can move by a displacement (dx, dy). This must obey max(abs(dx), abs(dy))) <= unit's max_move.
        - Attacking: You do not use dx/dy to attack. An enemy is in range if the Chebyshev distance between your unit and the target unit is valid: max(abs(attacker_x - target_x), abs(attacker_y - target_y)) <= attacker's range.
        REMEMBER: ALWAYS CHECK WHETHER YOUR MAXIMUM OF ABS(DX) AND ABS(DY) IS WITHIN THE UNIT'S MAX_MOVE LIMIT.
        IF YOU SEE THAT THE PREVIOUS ACTION WAS ILLEGAL (TRIED TO OCCUPY AN OCCUPIED TITLE OR SOMETHING ELSE), YOU MUST EITHER BE FOCUSED NOT TO REPEAT THE MISTAKE OR TO AVOID SUCH A TURN FOR A WHILE\n"""
