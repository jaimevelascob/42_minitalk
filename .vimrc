syntax on
"set list "$ at the end""
set number "see numbers"
set tabstop=4
set shiftwidth=4
set colorcolumn=80 "column size"
set autoindent
set expandtab
set clipboard=unnamed "CTRL+V"
set clipboard=unnamedplus "CNTRL+C"
set numberwidth=2
set mouse=a "move mouse"
set path+=**
set wildmenu "search files menu"
set relativenumber "number moving"
set hlsearch "Highlights search terms"
set showmatch "Highlights matching parentheses"
nnoremap <CR> :noh<CR> "quit the showmatch"
" Use clipboard as default register
if system('uname -s') == "Darwin\n"
  set clipboard=unnamed "OSX
else
  set clipboard=unnamedplus "Linux
endif
