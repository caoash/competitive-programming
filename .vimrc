set cin
set ai
set smarttab
set expandtab
set shiftwidth=4
set relativenumber
set tabstop=4
autocmd filetype cpp nnoremap<C-x> :!g++ % -std=c++17 -D mikey -Wall -Wshadow -Wextra -Wno-sign-compare -o %:r && ./%:r <CR>
" au BufNewFile *.cpp 0r ~/.vim/sf/template.cpp
autocmd filetype cpp nnoremap<C-b> :!g++ % -std=c++17 -D mikey -Wall -Wshadow -Wextra -Wno-sign-compare -o %:r <CR>
au BufNewFile *.cpp 0r ~/.vim/sf/template2.cpp
:nmap <c-s> :w<CR>
map <C-l> :tabnext<cr>
map <C-h> :tabprev<cr>
map <C-t> :tabnew <cr>
map <C-w> :q! <cr>
imap <c-s> <Esc>:w<CR>
map <C-z> <Nop>
set number
set wrap
set backspace=indent,eol,start
set mouse=a
set noeb vb t_vb=
color jellybeans
" color miramare 
syntax enable
set nocompatible             
filetype off                 
colorscheme jellybeans
set termguicolors

let &t_SI = "\<Esc>]50;CursorShape=1\x7" " Vertical bar in insert mode
let &t_EI = "\<Esc>]50;CursorShape=0\x7" " Block in normal mode

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin '907th/vim-auto-save'
Plugin 'SirVer/ultisnips'
Plugin 'honza/vim-snippets'
Plugin 'Valloric/YouCompleteMe'
Plugin 'mhartington/oceanic-next'
Plugin 'bfrg/vim-cpp-modern'
Plugin 'LaTeX-Box-Team/LaTeX-Box'
call vundle#end()
filetype plugin indent on
  
" let g:oceanic_next_terminal_bold = 1
" let g:oceanic_next_terminal_italic = 1
" colorscheme OceanicNext

let g:UltiSnipsExpandTrigger="<tab>"
let g:UltiSnipsJumpForwardTrigger="<c-b>"
let g:UltiSnipsJumpBackwardTrigger="<c-z>"
let g:auto_save = 1
let g:ycm_server_keep_logfiles = 1
let g:ycm_server_log_level = 'debug'
let g:UltiSnipsExpandTrigger="<c-j>"

let &t_SI = "\<esc>[5 q"  " blinking I-beam in insert mode
let &t_SR = "\<esc>[3 q"  " blinking underline in replace mode
let &t_EI = "\<esc>[ q"  " default cursor (usually blinking block) otherwise
let c_no_curly_error = 1
let g:cpp_no_function_highlight = 1
let g:cpp_simple_highlight = 1

