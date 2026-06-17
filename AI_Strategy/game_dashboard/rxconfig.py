import reflex as rx
from reflex_base.plugins.sitemap import SitemapPlugin

config = rx.Config(
    app_name="game_dashboard",
    frontend_port=3000,
    backend_port=8001,
    disable_plugins=[SitemapPlugin],
)
