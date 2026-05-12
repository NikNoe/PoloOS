# Configuration file for the Sphinx documentation builder.
# https://www.sphinx-doc.org/en/master/usage/configuration.html

import os
import sys

# ── Path setup ────────────────────────────────────────────────────────────────
# Add the yolo/ package directory to sys.path so autodoc can import the modules
# without requiring an installed package.
sys.path.insert(0, os.path.abspath("../../yolo"))

# ── Project information ───────────────────────────────────────────────────────
project   = "PoloOS — YOLO Pipeline"
author    = "NikNoe"
copyright = "2026, NikNoe"
release   = "0.1.0"

# ── General configuration ─────────────────────────────────────────────────────
extensions = [
    "sphinx.ext.autodoc",       # pulls docstrings from source files
    "sphinx.ext.napoleon",      # Google-style docstring parser
    "sphinx.ext.viewcode",      # adds [source] links next to documented items
    "sphinx.ext.intersphinx",   # cross-references to Python stdlib docs
]

# ── Napoleon (Google-style docstring) settings ────────────────────────────────
napoleon_google_docstring   = True
napoleon_numpy_docstring    = False
napoleon_include_init_with_doc       = True
napoleon_include_private_with_doc    = False
napoleon_include_special_with_doc    = True
napoleon_use_admonition_for_examples = True
napoleon_use_admonition_for_notes    = True
napoleon_use_rtype                   = True
napoleon_preprocess_types            = True

# ── Autodoc settings ──────────────────────────────────────────────────────────
autodoc_default_options = {
    "members":          True,   # document all public members
    "undoc-members":    True,   # include members without docstrings
    "show-inheritance": True,   # show base classes
    "member-order":     "bysource",  # preserve source file order
}
autodoc_typehints           = "description"   # render type hints in the body
autodoc_typehints_format    = "short"         # use short type names (int, not builtins.int)
autodoc_preserve_defaults   = True            # keep default argument values as written

# ── Intersphinx ───────────────────────────────────────────────────────────────
intersphinx_mapping = {
    "python": ("https://docs.python.org/3", None),
}

# ── HTML output ───────────────────────────────────────────────────────────────
html_theme = "furo"

html_theme_options = {
    "sidebar_hide_name": False,
    "navigation_with_keys": True,
    "light_css_variables": {
        "color-brand-primary":    "#00c8ff",
        "color-brand-content":    "#00c8ff",
        "color-admonition-background": "rgba(0, 200, 255, 0.05)",
    },
    "dark_css_variables": {
        "color-brand-primary":    "#00c8ff",
        "color-brand-content":    "#00c8ff",
    },
    "footer_icons": [],
}

html_title = "PoloOS — YOLO Pipeline"

# ── Source files ──────────────────────────────────────────────────────────────
templates_path    = ["_templates"]
exclude_patterns  = ["_build", "Thumbs.db", ".DS_Store"]
