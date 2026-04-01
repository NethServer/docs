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

extensions = [
    'sphinx_copybutton'
]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_book_theme'
html_static_path = ['_static']

# Theme options
html_theme_options = {
    "repository_url": "https://github.com/NethServer/docs",
    "use_repository_button": True,
    "use_download_button": False,
}

# Custom CSS for splash page styling
html_css_files = [
    'custom.css',
]

# Remove sidebar for a cleaner splash page
html_sidebars = {
    '**': []
}
