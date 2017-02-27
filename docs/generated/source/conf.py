import sys

# run doxygen
import subprocess, os
read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'
if read_the_docs_build:
    subprocess.call('cd ../doxygen; doxygen', shell=True)

# theme
import sphinx_rtd_theme
html_theme = "sphinx_rtd_theme"
html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]

# breathe
sys.path.append( "C:/Projects/ThirdParty/breathe" )
breathe_projects = { 
    "core": "C:/Projects/openfarm-core-avr/docs/generated/xml",
    "docs": "C:/Projects/openfarm-core-avr/"
}
breathe_default_project = "core"

source_parsers = {
   '.md': 'recommonmark.parser.CommonMarkParser',
}

extensions = [
    'sphinx.ext.autodoc',
    'breathe']
templates_path = ['_templates']
source_suffix = ['.rst', '.md']
master_doc = 'index'
project = u'openfarm-core-avr'
copyright = u'2017, Benjamin Jordan'
author = u'Benjamin Jordan'
version = u'0.1.0'
release = u'0.1.0'
language = None
exclude_patterns = []
pygments_style = 'sphinx'
todo_include_todos = False
html_static_path = ['_static']
htmlhelp_basename = 'openfarm-core-avrdoc'
man_pages = [
    (master_doc, 'openfarm-core-avr', u'openfarm-core-avr Documentation',
     [author], 1)
]
texinfo_documents = [
    (master_doc, 'openfarm-core-avr', u'openfarm-core-avr Documentation',
     author, 'openfarm-core-avr', 'One line description of project.',
     'Miscellaneous'),
]