# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'NethServer Documentation'
copyright = '2024, The NethServer project team'
author = 'The NethServer project team'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = []

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
html_static_path = ['_static']

# Theme options for a splash page
html_theme_options = {
    'description': 'Administrator\'s manual for all NethServer versions',
    'page_width': '980px',
    'sidebar_width': '0px',
    'body_max_width': '100%',
    'show_powered_by': False,
    'show_related': False,
    'fixed_sidebar': False,
}

# Custom CSS for splash page styling
html_css_files = [
    'custom.css',
]

# Remove sidebar for a cleaner splash page
html_sidebars = {
    '**': []
}
