"VIM help tips:
":help cmd    find normal mode command
":help i_cmd    find insert mode command
":help :cmd     find command-line command
":help  'option     find the option help
":set   option?     get the current value for the option

" Sections:
" ----------------------
" *> General
" *> Colors and Font
" *> Fileformat
" *> VIM userinterface
" ------ *> Statusline
" *> Visual
" *> Moving around and tab
" *> General Autocommand
" *> Parenthesis/bracket expanding
" *> General Abbrev
" *> Editing mappings etc.
" *> Command-line config
" *> Buffer realted
" *> Files and backup
" *> Folding
" *> Text option
" ------ *> Indent
" *> Spell checking
" *> Plugin configuration
" ------ *> Yank ring
" ------ *> File explorer
" ------ *> Minibuffer
" ------ *> Tag list (ctags) - not used
" ------ *> LaTeX Suite thing
" *> Filetype generic
" ------ *> Todo
" ------ *> VIM
" ------ *> HTML related
" ------ *> Ruby & PHP section
" ------ *> Python section
" ------ *> Cheetah section
" ------ *> Java section
" ------ *> JavaScript section
" ------ *> C mapping
" ------ *> SML
" ------ *> Scheme binding
" *> Snippet
" ------ *> Python
" ------ *> javaScript
" *> Cope
" *> MISC
"
" Tip:
" If you find anything that you can't understand than do this:
" help keyword OR helpgrep keyword
" Example:
" Go into command-line mode and type helpgrep nocompatible, ie.
" :helpgrep nocompatible
" then press <leader>c to see the results, or :botright cw
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => General
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Get out of VI's compatible mode..
set nocompatible

"Use Windows convension keys (C-c,C-x, etc)
source $VIMRUNTIME/mswin.vim
:behave mswin

"OS value. return win32 linux or mac
function! MySys()
    return "linux"
endfunction

"Set shell to be bash
if MySys() == "linux" || MySys() == "mac"
    set shell=bash
else
    set shell=c:\cygwin\bin\sh
endif

"Sets how many lines of history VIM har to remember
set history=400
set viminfo='20,<50,s10,h

"Enable filetype plugin
if has("eval")
    filetype plugin on
    filetype indent on
endif

"Set to auto read when a file is changed from the outside
set autoread

"Have the mouse enabled all the time:
set mouse=a

"Set mapleader
let mapleader = ","
let g:mapleader = ","

"Fast saving
nmap <leader>w :w!<cr>

" Use extend mouse mode to search word using SHIFT+left-mouse
set mousemodel=popup

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Colors and Font
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Enable syntax highlight
syntax on

"internationalization
"I only work in Win2k Chinese version
if has("multi_byte")
    set termencoding=chinese
    set encoding=utf-8
    " Set fileencoding priority
    if getfsize(expand("%")) > 0
        set fileencodings=ucs-bom,utf-8,cp936,big5,euc-jp,euc-kr,latin1
    else
        set fileencodings=cp936,big5,euc-jp,euc-kr,latin1
    endif
endif

"if you use vim in tty,
"'uxterm -cjk' or putty with option 'Treat CJK ambiguous characters as wide' on
if has("ambiwidth")
    set ambiwidth=double
endif

if has("gui_running")
    set guioptions-=l

    "colo darkblue

    if MySys()=="win32"
        "start gvim maximized
        if has("autocmd")
            au GUIEnter * simalt ~x
        endif
    endif
    if has("cursorline")
        set cursorline
        "hi cursorline guibg=#333333
        "hi CursorColumn guibg=#333333
    endif
endif

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Fileformat
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Favorite filetype
set fileformats=unix,dos

nmap <leader>fd :se ff=dos<cr>
nmap <leader>fu :se ff=unix<cr>

let g:explHideFiles='^\.,\.com$,\.doc$,\.pdf$,\.dvi$,\.gz$,\.exe$,\.zip$ \.ps$,\.ppt$'

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => VIM userinterface
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Set 7 lines to the curors - when moving vertical..
set scrolloff=7

"Turn on WiLd menu
set wildmenu

"Always show current position
set ruler

"The commandbar is 2 high
set cmdheight=2

"Show line number
set number

"Do not redraw, when running macros.. lazyredraw
set lazyredraw

"Change buffer - without saving
set hidden

"Set backspace
set backspace=indent,eol,start

"Bbackspace and cursor keys wrap to
set whichwrap+=<,>,h,l

"Ignore case when searching
set ignorecase
set incsearch

"Set magic on
set magic

"No sound on errors.
"set noerrorbells
"set visualbell	" when error, flash as visual bell 

"show matching bracet
set showmatch
set matchtime=5	" show matching time 

"How many tenths of a second to blink
set mat=5

"Highlight search thing
set hlsearch

"Set tab stop
set tabstop=4	" 实际的 tab 即为 4 个空格, tabstop = 4 is better for c programming
set shiftwidth=4  "设置自动缩进 4 个空格, 当然要设自动缩进先.
set softtabstop=4  "即设置 softtabstop 为 4. 输入 tab 后就跳了 4 格.
set expandtab    "在输入 tab 后, vim 用恰当的空格来填充这个 tab.

set whichwrap=b,s,<,>,[,]
set formatoptions=tcrqmB
set splitbelow
set nostartofline
set showcmd         " show (partial) command in status line
set showmode	" show editor mode, such as command, insert or replace, visual as messa 
set confirm		" with dialog support confirm({msg} [, {choices} [, {default} [, {type}]]])

" Make command line two lines high
set cmdheight=2

""""""""""""""""""""""""""""""
" => Statusline
""""""""""""""""""""""""""""""
"Always hide the statusline
set laststatus=2

function! CurDir()
    let curdir = substitute(getcwd(), '/home/wjiang4/', "~/", "g")
    return curdir
endfunction

"Format the statusline
set statusline=
set statusline+=%f "path to the file in the buffer, relative to current directory
set statusline+=\ %h%1*%m%r%w%0* " flag
set statusline+=\ [%{strlen(&ft)?&ft:'none'}, " filetype
set statusline+=%{&encoding}, " encoding
set statusline+=%{&fileformat}] " file format
" set statusline+=\ CWD:%r%{CurDir()}%h
set statusline+=\ (%l,%c)

""""""""""""""""""""""""""""""
" => Visual
""""""""""""""""""""""""""""""
" From an idea by Michael Naumann
function! VisualSearch(direction) range
    let l:saved_reg = @"
    execute "normal! vgvy"
    let l:pattern = escape(@", '\/.*$^~[]')
    let l:pattern = substitute(l:pattern, " $", "", "")
    if a:direction == 'b'
        execute "normal ?" . l:pattern . "^M"
    else
        execute "normal /" . l:pattern . "^M"
    endif
    let @/ = l:pattern
    let @" = l:saved_reg
endfunction

"Basically you press * or # to search for the current selection !! Really useful
vnoremap <silent> * :call VisualSearch('f')<CR>
vnoremap <silent> # :call VisualSearch('b')<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Moving around and tab page
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Map space to / and c-space to ?
map <space> /
"map <c-space> ?

"vmap    <Tab>         ^0   >
"vmap    <S-Tab>     ^0   <

" Cursor movement
nnoremap <Down> gj
nnoremap <Up> gk
vnoremap <Down> gj
vnoremap <Up> gk
inoremap <Down> <C-o>gj
inoremap <Up> <C-o>gk


nnoremap <End> g$
nnoremap <Home> g0
vnoremap <End> g$
vnoremap <Home> g0
inoremap <End> <C-o>g$
inoremap <Home> <C-o>g0

"Smart way to move btw. window
map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-h> <C-W>h
map <C-l> <C-W>l

"Actually, the tab does not switch buffers, but my arrow
"Bclose function ca be found in "Buffer related" section
map <leader>bd :Bclose<cr>
" Buffer switch
nnoremap <silent> <F6> :bn<CR> 
nnoremap <silent> <C-F6> :BN<CR> 
inoremap <silent> <F6> <ESC>:bn<CR>
inoremap <silent> <C-F6> <ESC>:BN<CR>

"Tab configuration
map <leader>tn :tabnew %<cr>
map <leader>tc :tabclose<cr>
map <leader>tm :tabmove
if has("usetab")
    set switchbuf=usetab
endif

if has("stal")
    set showtabline=2
endif

"Moving fast to front, back and 2 sides ;)
imap <m-$> <esc>$a
imap <m-0> <esc>0i
imap <D-$> <esc>$a
imap <D-0> <esc>0i

"==========================================================
"show tabs/ hide tabs / naviguate through tabs
"==========================================================
"tab labels show the filename without path(tail) (see :help statusline for options)
:set guitablabel=%t\ %M

" tab navigation (next tab or next buffer) with alt left / alt right
map <silent><A-Right> :tabnext<CR>
map <silent><A-Left>  :tabprevious<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => General Autocommand
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" To automatically cd to the directory of current open file
:autocmd BufEnter * cd %:p:h

"autocmd BufNewFile *.cpp 0r ~/.vim/skeleton/skeleton.cpp
"autocmd BufNewFile *.h 0r ~/.vim/skeleton/skeleton.h

"Switch to current dir
"map <leader>cd :cd %:p:h<cr>

"filetype on
autocmd FileType c,cpp,java set cindent
autocmd FileType text setlocal textwidth=80	"For text mode, set textwidth =78 such as write email
autocmd FileType plugin indent on	"For all plugin filetype let indent on
autocmd FileType ftplugin indent on	"For all filetype plugin let indent on

autocmd BufNewFile,BufRead *.xsl		map <F6> <ESC>:call XslTags()<CR><CR><CR>
:function XslTags()
	:grep ":template .*$" %
	:copen 23
:endfunction

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Parenthesis/bracket expanding
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
vnoremap $1 <esc>`>a)<esc>`<i(<esc>
")
vnoremap $2 <esc>`>a]<esc>`<i[<esc>
vnoremap $3 <esc>`>a}<esc>`<i{<esc>
vnoremap $$ <esc>`>a"<esc>`<i"<esc>
vnoremap $q <esc>`>a'<esc>`<i'<esc>
vnoremap $w <esc>`>a"<esc>`<i"<esc>

"Map auto complete of (, ", ', [
"http://www.vim.org/tips/tip.php?tip_id=153
"
ino ( ()<esc>:let leavechar=")"<cr>i
ino { {}<esc>:let leavechar="}"<cr>i
ino $q ''<esc>:let leavechar="'"<cr>i
ino $w ""<esc>:let leavechar='"'<cr>i
imap <c-l> <esc>:exec "normal f" . leavechar<cr>a

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Editing mappings etc.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Remap VIM 0
map 0 ^

"Move a line of text using control
nmap <M-j> mz:m+<cr>`z
nmap <M-k> mz:m-2<cr>`z
vmap <M-j> :m'>+<cr>`<my`>mzgv`yo`z
vmap <M-k> :m'<-2<cr>`>my`<mzgv`yo`z

if MySys() == "mac"
    nmap <D-j> <M-j>
    nmap <D-k> <M-k>
    vmap <D-j> <M-j>
    vmap <D-k> <M-k>
endif

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Command-line config
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
func! Cwd()
    let cwd = getcwd()
    return "e " . cwd
endfunc

func! DeleteTillSlash()
    let g:cmd = getcmdline()
    if MySys() == "linux" || MySys() == "mac"
        let g:cmd_edited = substitute(g:cmd, "\(.*[/]\).*", "\1", "")
    else
        let g:cmd_edited = substitute(g:cmd, "\(.*[\\]\).*", "\1", "")
    endif
    if g:cmd == g:cmd_edited
        if MySys() == "linux" || MySys() == "mac"
            let g:cmd_edited = substitute(g:cmd, "\(.*[/]\).*/", "\1", "")
        else
            let g:cmd_edited = substitute(g:cmd, "\(.*[\\]\).*[\\]", "\1", "")
        endif
    endif
    return g:cmd_edited
endfunc

func! CurrentFileDir(cmd)
    return a:cmd . " " . expand("%:p:h") . "/"
endfunc

"cno $q <C->eDeleteTillSlash()<cr>
"cno $c e <C->eCurrentFileDir("e")<cr>
"cno $tc <C->eCurrentFileDir("tabnew")<cr>
cno $th tabnew ~/
cno $td tabnew ~/Desktop/

"Bash like
cno <C-A> <Home>
cno <C-E> <End>
cno <C-K> <C-U>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Buffer realted
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Open a dummy buffer for paste
map <leader>q :e ~/buffer<cr>

" Buffer - reverse everything ... :)
map <F9> ggVGg?

" Don't close window, when deleting a buffer
command! Bclose call <SID>BufcloseCloseIt()

function! <SID>BufcloseCloseIt()
    let l:currentBufNum = bufnr("%")
    let l:alternateBufNum = bufnr("#")

    if buflisted(l:alternateBufNum)
        buffer #
    else
        bnext
    endif

    if bufnr("%") == l:currentBufNum
        new
    endif

    if buflisted(l:currentBufNum)
        execute "bdelete! ".l:currentBufNum
    endif
endfunction

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Files and backup
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Turn backup off
set nobackup
set nowb
"set noswapfile
set noar

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Folding
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Enable folding, I find it very useful
set fen
set fdl=0

""""""""""""""""""""""""""""""
" => Indent
""""""""""""""""""""""""""""""
"Auto indent
set autoindent

"Smart indet
set smartindent

"C-style indenting
set cindent
set cino=:0g0t0(sus  " values control how cindent indent code

"Wrap line
set wrap

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Plugin configuration
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""""""""""""""""""""""""""""""
" => File explorer
""""""""""""""""""""""""""""""
"Split vertically
let g:explVertical=1

"Window size
let g:explWinSize=35

let g:explSplitLeft=1
let g:explSplitBelow=1

"Hide some file
let g:explHideFiles='^.,.*.class$,.*.swp$,.*.pyc$,.*.swo$,.DS_Store$'

"Hide the help thing..
let g:explDetailedHelp=0

""""""""""""""""""""""""""""""
" => Minibuffer
""""""""""""""""""""""""""""""
let g:miniBufExplModSelTarget = 1
let g:miniBufExplorerMoreThanOne = 0
let g:miniBufExplModSelTarget = 0
let g:miniBufExplUseSingleClick = 1
let g:miniBufExplMapWindowNavVim = 1
let g:miniBufExplVSplit = 25
let g:miniBufExplSplitBelow=1

"WindowZ
map <c-w><c-t> :WMToggle<cr>

let g:bufExplorerSortBy = "name"

""""""""""""""""""""""""""""""
" => CTags
""""""""""""""""""""""""""""""
:set tags=tags;,TAGS;,/usr/include/tags


""""""""""""""""""""""""""""""
" => Sketch
""""""""""""""""""""""""""""""
command -nargs=0 ToggleSketch call ToggleSketch()

""""""""""""""""""""""""""""""
" =>  WinManager
""""""""""""""""""""""""""""""
let g:winManarWindowLayout = "FileExplorer"
map <c-w><c-f> :FirstExplorerWindow<cr>
map <c-w><c-b> :BottomExplorerWindow<cr>

""""""""""""""""""""""""""""""
" =>  Tlist
""""""""""""""""""""""""""""""
let Tlist_Use_Right_Window=1
let Tlist_File_Fold_Auto_Close=1
let Tlist_Compact_Format=1
let Tlist_Display_Prototype=0
let Tlist_Show_One_File=1
let Tlist_Sort_Type="name"
let Tlist_GainFocus_On_ToggleOpen=1
let Tlist_Close_On_Select=1

""""""""""""""""""""""""""""""
" =>  latexSuite
""""""""""""""""""""""""""""""
filetype plugin on
set grepprg=grep\ -nH\ $*
let g:Tex_CompileRule_dvi
    \="latex -src-specials -interaction=nonstopmode $*"
let g:Tex_ViewRule_dvi
    \="xdvi -editor 'gvim --servername latex-suite --remote-silent'"

""""""""""""""""""""""""""""""
" =>  Calendar
""""""""""""""""""""""""""""""
"let g:calendar_diary=<PATH>
let g:calendar_focus_today = 1
let g:calendar_weeknm = 1 " WK01
"map <F12>   :Calendar<cr>
"imap <C-F12>   <C-R>=strftime("<!-- Y%YM%mD%d %X -->")<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => MISC
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"Remove the Windows ^M
noremap <Leader>m :%s/\r//g<CR>

"Paste toggle - when pasting something in, don't indent.
"set pastetoggle=<F3>

"Remove indenting on empty line
map <F2> :%s/s*$//g<cr>:noh<cr>''

" Always print line number
set printoptions=number:y

" Hide the mouse pointer while typing
set mousehide

set autochdir

" vimdiff : use a large window
if &diff
    se co=160
endif
    
" set default browse dir
set browsedir=buffer


function TimeStamp()
    let curposn= SaveWinPosn()
    %s/\$Date: .*\$/\=strftime("$Date: %Y-%m-%d %H:%M:%S$")/ge
    %s/Last Change: .*$/\=strftime("Last Change: %Y-%m-%d %H:%M:%S")/ge
    %s/Last Modified: .*$/\=strftime("Last Modified: %Y-%m-%d %H:%M:%S")/ge
    call RestoreWinPosn(curposn)
endfunction


function AutoTimeStamp()
    augr tagdate
    au!
    au BufWritePre,FileWritePre * call TimeStamp()
    augr END
endfunction
" call AutoTimeStamp()

function NoAutoTimeStamp()
    augr tagdate
    au!
    augr END
endfunction

" my functions
:function BreakPoint()
	:let gdbinit = "$HOME/.gdbinit"
	:let setting = readfile(gdbinit)
	:let currentline = line(".")
	:let fname = bufname("%")
	:let breakcmd = printf("break	%s:%s", fname, currentline)
	:let newbreak = [breakcmd]
	:let setting += newbreak
	:let setting += [''] " add a new line at EOF
	:echo "break point : "
	:echo breakcmd
	:call writefile(setting, gdbinit) 
:endfunction


map <F5> :WMToggle<cr>

map <F7>	<ESC>:cd $CSRC/query<CR>:make xpath2cmd<CR>
map <C-N>	<ESC>:cn<CR>
map <C-P>	<ESC>:cp<CR>

map <F4>	<ESC>:call BreakPoint()<CR>


map <F12>	<ESC>:Tlist<CR>:TlistUpdate<CR><C-L>
map <C-F12> <ESC>:!cd $CSRC; ctags -R --c++-kinds=+p --fields=+iaS include parse/include parse/esii query/xpath2ast query/include query/type query/xpath2run query/xpath2cc<CR>
nnoremap <silent> <S-F12> <ESC>:TlistSync<CR>


