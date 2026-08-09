# Took a Pill in Ibiza

A short (30-45 min), irreversible, high-agency mind-trip experience. First-person interactive
story that slowly replaces its own rules with living systems responding to how the player
moves, looks, and feels — until the software permanently locks itself so the player can never
take the trip again.

Engine: Unreal Engine 5 (C++ core systems + Blueprint content layer), modular and data-driven.

## Status

Pre-production / vertical slice scaffolding. See [`Docs/TECHNICAL_DESIGN.md`](Docs/TECHNICAL_DESIGN.md)
for the living design & architecture document — it is the source of truth and is updated with
every significant change.

## Repo structure

```
Docs/               Living design doc, architecture notes, progress log
Source/OnePill/      C++ gameplay modules
Content/             UE5 content (Blueprints, materials, audio, levels) — placeholder until
                     assets are authored in-editor
Config/              UE5 project/engine config
```

## Working process

- Smallest possible vertical increments, one commit per meaningful change.
- Every change is pushed immediately — the repo should always be in a clean, pullable state.
- Design decisions and their rationale live in `Docs/TECHNICAL_DESIGN.md`, not in commit messages.
