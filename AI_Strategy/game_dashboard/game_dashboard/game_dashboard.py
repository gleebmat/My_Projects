import warnings

warnings.filterwarnings("ignore", category=DeprecationWarning)

import reflex as rx
from game_dashboard.state import AppState
from game_dashboard.components import match_list, detail_panel

GLOBAL_CSS = """
*, *::before, *::after { box-sizing: border-box; }
html, body {
    background: #0e0e0d !important;
    color: #d4d3d0 !important;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
    margin: 0; padding: 0;
}
.radix-themes {
    background: #0e0e0d !important;
    --color-background: #0e0e0d !important;
}
[data-radix-scroll-area-viewport],
.rt-TableRoot, .rt-TableRow, .rt-TableCell,
.rt-TableColumnHeaderCell, .rt-TableHeader,
.rt-TableBody {
    background: transparent !important;
    border-color: #2a2927 !important;
    color: #d4d3d0 !important;
}
.rt-TableRoot[data-variant=surface] {
    background: #1a1917 !important;
    border: 1px solid #2a2927 !important;
    border-radius: 8px !important;
    overflow: hidden;
}
.rt-TableColumnHeaderCell {
    background: #141412 !important;
    border-bottom: 1px solid #2a2927 !important;
}
"""


def header() -> rx.Component:
    return rx.box(
        rx.hstack(
            rx.hstack(
                rx.html(
                    """<svg width="28" height="28" viewBox="0 0 28 28" fill="none"
                        xmlns="http://www.w3.org/2000/svg" aria-label="Logo">
                      <circle cx="14" cy="14" r="12" stroke="#2dd4bf" stroke-width="1.5"/>
                      <circle cx="14" cy="14" r="5" stroke="#2dd4bf" stroke-width="1.5"/>
                      <line x1="14" y1="2" x2="14" y2="8" stroke="#2dd4bf" stroke-width="1.5" stroke-linecap="round"/>
                      <line x1="14" y1="20" x2="14" y2="26" stroke="#2dd4bf" stroke-width="1.5" stroke-linecap="round"/>
                      <line x1="2" y1="14" x2="8" y2="14" stroke="#2dd4bf" stroke-width="1.5" stroke-linecap="round"/>
                      <line x1="20" y1="14" x2="26" y2="14" stroke="#2dd4bf" stroke-width="1.5" stroke-linecap="round"/>
                    </svg>""",
                    style={"display": "flex", "align_items": "center"},
                ),
                rx.vstack(
                    rx.text(
                        "Game State API",
                        size="3",
                        weight="bold",
                        letter_spacing="-0.01em",
                        color="#e8e7e4",
                    ),
                    rx.text("AI Telemetry Dashboard", size="1", color="#78776f"),
                    spacing="0",
                    align="start",
                    gap="0",
                ),
                spacing="3",
                align="center",
            ),
            rx.hstack(
                rx.cond(
                    AppState.error != "",
                    rx.box(
                        rx.text(AppState.error, size="1", color="#f87171"),
                        padding="0.4rem 0.75rem",
                        background="#2a1515",
                        border="1px solid #7f1d1d",
                        border_radius="6px",
                    ),
                    rx.fragment(),
                ),
                rx.button(
                    rx.cond(
                        AppState.loading,
                        rx.spinner(size="1"),
                        rx.icon("refresh-cw", size=13),
                    ),
                    rx.text("Refresh", size="2"),
                    on_click=AppState.load_matches,
                    disabled=AppState.loading,
                    style={
                        "background": "#134e4a",
                        "color": "#2dd4bf",
                        "border": "1px solid #0f766e",
                        "border_radius": "8px",
                        "padding": "0.4rem 0.875rem",
                        "cursor": "pointer",
                        "display": "flex",
                        "gap": "0.4rem",
                        "align_items": "center",
                    },
                ),
                spacing="3",
                align="center",
            ),
            justify="between",
            align="center",
            width="100%",
        ),
        padding="0.75rem 1.5rem",
        background="#0e0e0d",
        border_bottom="1px solid #2a2927",
        position="sticky",
        top="0",
        z_index="100",
    )


def index() -> rx.Component:
    return rx.box(
        rx.el.style(GLOBAL_CSS),
        header(),
        rx.hstack(
            rx.box(
                match_list(),
                width="280px",
                min_width="280px",
                height="calc(100vh - 57px)",
                overflow_y="auto",
                border_right="1px solid #2a2927",
                background="#0b0b0a",
            ),
            rx.box(
                detail_panel(),
                flex="1",
                height="calc(100vh - 57px)",
                overflow_y="auto",
                background="#0e0e0d",
            ),
            spacing="0",
            width="100%",
            align="start",
        ),
        min_height="100vh",
        background="#0e0e0d",
        on_mount=AppState.load_matches,
    )


app = rx.App(
    theme=rx.theme(
        appearance="dark",
        accent_color="teal",
        radius="medium",
    ),
)
app.add_page(index, route="/")
