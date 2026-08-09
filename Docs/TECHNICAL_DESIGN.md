# Took a Pill in Ibiza — Living Technical Design & Architecture Document

Status: living document, updated with every significant change.
Last updated: 2026-08-09 — initial creation.

## 1. Vision

Working title: **Took a Pill in Ibiza**

A 30-45 minute, irreversible, high-agency mind-trip. Begins as a polished first-person
interactive story, then progressively hands control of the world's rules to living systems
that respond to how the player moves, looks, and feels — culminating in a permanent,
one-time device lock. The craving the player feels afterward, unable to replay it, is the
designed emotional payload, not a bug.

Simultaneously a game, a cinematic piece, and a living experience. Tightly contained but must
feel open and exploratory. Every second intentional — quality over quantity.

## 2. Core Themes

- The modern hunger for peak intensity and transcendence.
- The impossibility of staying in the sublime.
- Desire, memory, ego dissolution, the quiet loneliness/craving after the peak.
- The permanent lock is the thematic climax, not a technical gimmick.

## 3. Art Direction — Liquid Psychedelic Surrealism

- Soft, flowing, liquid, hand-crafted-feeling forms.
- Palette: deep violet, electric teal, warm amber, crushed raspberry, soft gold, moments of
  luminous white.
- Painterly edges blended with smooth 3D; subtle analog film grain, gentle chromatic
  aberration, soft glow, organic distortion.
- Architecture and bodies breathe/melt slowly — never chaotic or noisy.
- High-fashion editorial lighting through an elevated classic-psychedelic lens.
- Avoid: fractal overload, neon cyberpunk, cartoon/cel-shaded looks.
- Target feeling: expensive, dreamy, slightly dangerous, memorable.

## 4. Music Direction — Modern Psychedelic Rock / Neo-Psych

- Warm analog synths, swirling guitars, organic drums, reverb-drenched textures.
- Arc: intimate hazy sunset passages → dense swirling peaks → spacious afterglow.
- Pre-authored stems mixed in real time by an adaptive engine driven by player signals and an
  intensity curve. Music is a character, not a soundtrack — it scores and responds.

## 5. Experience Structure

1. **Pre-Pill** (8-12 min): stylish, slightly unreal contained space. Full normal first-person
   controls. Reads as a polished short interactive story.
2. **Swallow sequence**: deliberate, physical point of no return.
3. **Post-Pill**: living systems progressively replace normal rules while full player agency is
   retained. World responds to player movement and gaze.
4. **Peak → Integration/Comedown → Final collapse into light → Permanent lock message →
   optional Echo generation.**

## 6. Core Systems (architecture intent)

| System | Purpose | Notes |
|---|---|---|
| Living Rule Graph | Lightweight director continuously rewires environment behaviors | Data-driven graph, not hardcoded scripted events |
| Player Signal Layer | Gaze direction, movement speed/stillness, interaction style (aggressive vs tender), optional biometric proxies | Feeds the director and adaptive music engine |
| Gaze-contingent resolution | Objects fully resolve only when stared at | Ties rendering/detail budget to attention, reinforces theme |
| Soft interaction physics | Touched objects yield, breathe, leave residual motion, "remember" the player | Distinct from standard rigid-body physics |
| Adaptive stem music engine | Real-time mix of pre-authored stems driven by intensity curve + signals | Wwise or MetaSounds-driven |
| One-time device lock + Echo generator | Cryptographic permanent lock; 15-30s non-replayable shareable fragment derived from that specific playthrough | Thematic climax — must be reliable and genuinely irreversible |

## 7. Proposed Technical Architecture

- **Engine**: UE5, C++ core / Blueprint content layer hybrid.
- **Module layout** (`Source/OnePill/`):
  - `Core/` — game mode, game state, save/lock persistence
  - `Signals/` — player signal capture (gaze, movement, interaction style)
  - `Director/` — Living Rule Graph evaluator, data-driven rule assets
  - `Audio/` — adaptive music engine glue (MetaSounds/Wwise integration)
  - `Interaction/` — soft interaction physics component
  - `Lock/` — one-time cryptographic lock + Echo generation
- **Data-driven philosophy**: rules, intensity curves, and stem mappings live as
  `UDataAsset`/`UPrimaryDataAsset` instances editable by designers, not hardcoded in C++.
- **ECS-friendly**: prefer component composition (ActorComponents) over deep inheritance so
  systems can be mixed onto any actor.

## 8. Risks (flagged early, revisit as work progresses)

- **Scope**: system list is ambitious for a 30-45 min experience; must ruthlessly prioritize
  what's perceivable in a single playthrough.
- **Lock reliability**: a "permanent" lock that fails to persist (reinstall, save-scumming,
  file deletion) breaks the thematic promise — needs a real design decision on what "permanent"
  means technically (device-bound key, telemetry-backed, etc.) before implementation.
- **Emotional tone**: post-pill systems must stay legible enough that agency doesn't collapse
  into frustration — living systems need guardrails.
- **Performance**: gaze-contingent resolution and soft-body interaction physics are both
  potentially expensive; needs early profiling budget.
- **Tooling gap**: current dev environment has no UE5 editor instance available to this
  assistant — C++/data/doc scaffolding can be authored and committed here, but in-editor steps
  (Blueprint wiring, material graphs, level dressing) need to be executed by a human with the
  editor open, following the precise steps logged in this doc.

## 9. Progress Log

- **2026-08-09**: Repository created (`OnePill`, public). Initial skeleton: README, this
  document, `.gitignore`, folder structure. No code yet.
