function varargout = simplex(varargin)
% SIMPLEX M-file for simplex.fig
%      SIMPLEX, by itself, creates a new SIMPLEX or raises the existing
%      singleton*.
%
%      H = SIMPLEX returns the handle to a new SIMPLEX or the handle to
%      the existing singleton*.
%
%      SIMPLEX('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SIMPLEX.M with the given input arguments.
%
%      SIMPLEX('Property','Value',...) creates a new SIMPLEX or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before simplex_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to simplex_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Copyright 2002-2003 The MathWorks, Inc.

% Edit the above text to modify the response to help simplex

% Last Modified by GUIDE v2.5 13-Nov-2018 11:03:38

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @simplex_OpeningFcn, ...
                   'gui_OutputFcn',  @simplex_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before simplex is made visible.
function simplex_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to simplex (see VARARGIN)

% Choose default command line output for simplex
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes simplex wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = simplex_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function A_Callback(hObject, eventdata, handles)
% hObject    handle to A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of A as text
%        str2double(get(hObject,'String')) returns contents of A as a double


% --- Executes during object creation, after setting all properties.
function A_CreateFcn(hObject, eventdata, handles)
% hObject    handle to A (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function znak_Callback(hObject, eventdata, handles)
% hObject    handle to znak (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of znak as text
%        str2double(get(hObject,'String')) returns contents of znak as a double


% --- Executes during object creation, after setting all properties.
function znak_CreateFcn(hObject, eventdata, handles)
% hObject    handle to znak (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function b_Callback(hObject, eventdata, handles)
% hObject    handle to b (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of b as text
%        str2double(get(hObject,'String')) returns contents of b as a double


% --- Executes during object creation, after setting all properties.
function b_CreateFcn(hObject, eventdata, handles)
% hObject    handle to b (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end


% --- Executes on button press in Dugme.
function Dugme_Callback(hObject, eventdata, handles)
% hObject    handle to Dugme (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

A = str2num(get(handles.A,'string'));
b = str2num(get(handles.b,'string'));
c = str2num(get(handles.c,'string'));

%[x_opt, f_opt] = linprog(-c,A,b);
[x_opt, f_opt] = rijesi_simplex(A,b,c);

set(handles.x,'string',mat2str(x_opt'));
set(handles.f,'string',num2str(f_opt));

function c_Callback(hObject, eventdata, handles)
% hObject    handle to c (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of c as text
%        str2double(get(hObject,'String')) returns contents of c as a double


% --- Executes during object creation, after setting all properties.
function c_CreateFcn(hObject, eventdata, handles)
% hObject    handle to c (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function x_Callback(hObject, eventdata, handles)
% hObject    handle to x (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of x as text
%        str2double(get(hObject,'String')) returns contents of x as a double


% --- Executes during object creation, after setting all properties.
function x_CreateFcn(hObject, eventdata, handles)
% hObject    handle to x (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function f_Callback(hObject, eventdata, handles)
% hObject    handle to f (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of f as text
%        str2double(get(hObject,'String')) returns contents of f as a double


% --- Executes during object creation, after setting all properties.
function f_CreateFcn(hObject, eventdata, handles)
% hObject    handle to f (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end




% --------------------------------------------------------------------
function Datoteka_Callback(hObject, eventdata, handles)
% hObject    handle to Datoteka (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



% --------------------------------------------------------------------
function load_Callback(hObject, eventdata, handles)
% hObject    handle to load (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    [datoteka,putanja] = uigetfile('*.mat','Izaberi Mat datoteku');
% Ako korisnik izabere "Cancel" samo zatvori dialog
if isequal([datoteka,putanja],[0,0])
 return
% inace konstruisi puno ime i otvori datoteku
else
 File = fullfile(putanja,datoteka);

 % Zapamti koja je datoteka otvorena radi cuvanja
 handles.LastFile = File;

 % load podatke iz datoteke
 load(File);

 % Pridruzi ucitane podatke variablama na formi
 set(handles.A,'String',num2str(A,'%10.2f'));
 set(handles.b,'String',num2str(b,'%10.2f'));
 set(handles.c,'String',num2str(c,'%10.2f'));

 % Primjeni nove vrijednosti variabli na formi
 guidata(hObject, handles)
end

function save_Callback(hObject, eventdata, handles)
    A = str2num(get(handles.A,'String'));
b = str2num(get(handles.b,'String'));
c = str2num(get(handles.c,'String'));
% Sacuvaj podatke u otvorenu datoteku
if isfield(handles,'LastFile')
 File = handles.LastFile;
else
 % Omoguci korisniku da izabere ime datoteke
 [filename, pathname] = uiputfile('*.mat','Sacuvaj kao');
 % Ako korisnik izabere "Cancel" samo zatvori dialog
 if isequal([filename,pathname],[0,0])
 return
 else
 % inace konstruisi puno ime i sacuvaj podatke u datoteku
 File = fullfile(pathname,filename);
 end
end
save(File,'A','b','c')

function save_as_Callback(hObject, eventdata, handles)
    A = str2num(get(handles.A,'String'));
b = str2num(get(handles.b,'String'));
c = str2num(get(handles.c,'String'));
% Omoguci korisniku da izabere ime datoteke
[filename, pathname] = uiputfile('*.mat','Sacuvaj kao');
% Ako korisnik izabere "Cancel" samo zatvori dialog
if isequal([filename,pathname],[0,0])
 return
else
 % inace konstruisi puno ime i sacuvaj podatke u datoteku
 File = fullfile(pathname,filename);
 save(File,'A','b','c')
end
