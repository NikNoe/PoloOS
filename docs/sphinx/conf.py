import os, sys

project = "PoloOS — Qt Dashboard"
author  = "NikNoe"
release = "0.1"
language = "en"

extensions = [
    "sphinx.ext.autodoc",
    "sphinx.ext.napoleon",
    "sphinx.ext.viewcode",
]

napoleon_google_docstring = True
napoleon_numpy_docstring  = False

html_theme = "furo"
html_theme_options = {
    "light_css_variables": {"color-brand-primary": "#00c8ff"},
    "dark_css_variables":  {"color-brand-primary": "#00c8ff"},
}
