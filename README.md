# Took a Pill in Ibiza

A 30-45 minute, first-person, irreversible experience: a polished narrative opening that progressively hands control of the world's rules to living systems reacting to how the player moves, looks, and stays still — until the game permanently locks itself on that device. Unreal Engine 5, C++ core systems with a Blueprint content layer.

## Status

Pre-production / vertical slice scaffolding. Core gameplay systems are implemented in C++; level content, art, and audio are not yet authored. [`Docs/TECHNICAL_DESIGN.md`](Docs/TECHNICAL_DESIGN.md) is a living design document — architecture and rationale live there, not in commit messages, and it's updated with every significant change.

## The systems

The design problem this repo solves: a game whose behavior *changes* mid-experience without hardcoding that change into level blueprints. Four systems, cleanly separated by responsibility:

- **`PlayerSignalComponent`** (Signals) — a pure observer. Tracks gaze direction, normalized movement speed, and continuous stillness duration, and exposes them as read-only signals. It never modifies gameplay itself — it's the sensor layer for everything downstream (the Living Rule Graph, and eventually an adaptive music engine and gaze-contingent resolution system).
- **`LivingRuleAsset`** (Director) — a `UPrimaryDataAsset`, not code. Each asset names a signal to watch, a normalized activation threshold, and a `BehaviorTag` to broadcast when crossed — so designers author new world reactions without touching C++.
- **`DirectorComponent`** (Director) — evaluates every assigned rule each tick against the owner's signal component and broadcasts `OnLivingRuleActivated(BehaviorTag)` for whichever cross their threshold. The Director never touches world actors directly; actors subscribe to the tags they care about. That indirection is the whole point — it's what lets "world reacts to player" stay data-driven instead of an ever-growing switch statement.
- **`SwallowTrigger` → `DeviceLockSubsystem`** (Core / Lock) — `SwallowTrigger` is the one boundary in the experience that cannot be undone: firing it notifies the Director that post-pill-only rules may now activate. `DeviceLockSubsystem` (a `UGameInstanceSubsystem`) is checked before the pre-pill sequence is allowed to start at all, and once the experience completes it writes a permanent marker — outside normal save-game slots, on purpose — so the game cannot be started again on that device. The README doesn't oversell this: v1's lock is a hashed device+install marker file, explicitly not hardened against a user who wipes app data, with the open question tracked as a design risk in the technical design doc rather than silently ignored.

## Repo structure

```
Docs/                        living design & architecture doc, progress log
Source/OnePill/
  Core/                       character, game mode, the swallow trigger
  Director/                   DirectorComponent, LivingRuleAsset
  Signals/                    PlayerSignalComponent
  Lock/                       DeviceLockSubsystem
Content/                      UE5 content — placeholder until assets are authored in-editor
Config/                       UE5 project/engine config
```

## Working process

Smallest possible vertical increments, one commit per meaningful change, repo kept in a clean pullable state at all times.
