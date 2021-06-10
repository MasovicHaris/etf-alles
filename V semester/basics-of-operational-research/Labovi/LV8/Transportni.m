function varargout = Transportni(varargin)
% TRANSPORTNI M-file for Transportni.fig
%      TRANSPORTNI, by itself, creates c new TRANSPORTNI or raises the existing
%      singleton*.
%
%      H = TRANSPORTNI returns the handle to c new TRANSPORTNI or the handle to
%      the existing singleton*.
%
%      TRANSPORTNI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TRANSPORTNI.M with the given input arguments.
%
%      TRANSPORTNI('Property','Value',...) creates c new TRANSPORTNI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Simpleks2_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Transportni_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Copyright 2002-2003 The MathWorks, Inc.

% Edit the above text to modify the response to help Transportni

% Last Modified by GUIDE v2.5 27-Mar-2009 13:00:49

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Transportni_OpeningFcn, ...
                   'gui_OutputFcn',  @Transportni_OutputFcn, ...
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


% --- Executes just before Transportni is made visible.
function Transportni_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Transportni (see VARARGIN)

% Choose default command line output for Transportni
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Transportni wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Transportni_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function C_Callback(hObject, eventdata, handles)
% hObject    handle to C (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C as text
%        str2double(get(hObject,'String')) returns contents of C as c double


% --- Executes during object creation, after setting all properties.
function C_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have c white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function b_Callback(hObject, eventdata, handles)
% hObject    handle to b (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of b as text
%        str2double(get(hObject,'String')) returns contents of b as c double


% --- Executes during object creation, after setting all properties.
function b_CreateFcn(hObject, eventdata, handles)
% hObject    handle to b (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have c white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as c double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have c white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



% --------------------------------------------------------------------
function menu_otvori_Callback(hObject, eventdata, handles)
% hObject    handle to menu_otvori (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
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
    
    % Ucitaj podatke iz datoteke
    load(File);
    
    % Pridruzi ucitane podatke variablama na formi
    set(handles.C,'String',num2str(C));
    set(handles.I,'String',num2str(I));
    set(handles.O,'String',num2str(O));
    
    % Primjeni nove vrijednosti variabli na formi
    guidata(hObject, handles)
end


% --------------------------------------------------------------------
function menu_sacuvaj_Callback(hObject, eventdata, handles)
% hObject    handle to menu_sacuvaj (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

C  = str2num(get(handles.C,'String'));
I  = str2num(get(handles.I,'String'));
O  = str2num(get(handles.O,'String'));

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

save(File,'C','I','O');


% --------------------------------------------------------------------
function menu_sacuvaj_kao_Callback(hObject, eventdata, handles)
% hObject    handle to menu_sacuvaj_kao (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

C  = str2num(get(handles.C,'String'));
I  = str2num(get(handles.I,'String'));
O  = str2num(get(handles.O,'String'));

% Omoguci korisniku da izabere ime datoteke
[filename, pathname] = uiputfile('*.mat','Sacuvaj kao');

% Ako korisnik izabere "Cancel" samo zatvori dialog
if isequal([filename,pathname],[0,0])
    return
else
    % inace konstruisi puno ime i sacuvaj podatke u datoteku
    File = fullfile(pathname,filename);
    save(File,'C','I','O')
end

% --------------------------------------------------------------------
function Datoteka_Callback(hObject, eventdata, handles)
% hObject    handle to Datoteka (see GCBO)
% eventdata  reserved - to be defined in c future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)








function P_Callback(hObject, eventdata, handles)
% hObject    handle to P (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of P as text
%        str2double(get(hObject,'String')) returns contents of P as a double


% --- Executes during object creation, after setting all properties.
function P_CreateFcn(hObject, eventdata, handles)
% hObject    handle to P (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function K_Callback(hObject, eventdata, handles)
% hObject    handle to K (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of K as text
%        str2double(get(hObject,'String')) returns contents of K as a double


% --- Executes during object creation, after setting all properties.
function K_CreateFcn(hObject, eventdata, handles)
% hObject    handle to K (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in Dugme_P.
function Dugme_P_Callback(hObject, eventdata, handles)
% hObject    handle to Dugme_P (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
matricaCijena = str2num(get(handles.C,'string'));
izvorista = str2num(get(handles.I,'string'));
odredista = str2num(get(handles.O,'string'));
[R,~,~,~] = sjeveroZapad(matricaCijena, izvorista, odredista);
set(handles.P,'string',num2str(R));


% --- Executes on button press in Dugme_K.
function Dugme_K_Callback(hObject, eventdata, handles)
% hObject    handle to Dugme_K (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
matricaCijena = str2num(get(handles.C,'string'));
izvorista = str2num(get(handles.I,'string'));
odredista = str2num(get(handles.O,'string'));
[R, matricaCijenaNova, ~, ~] = sjeveroZapad(matricaCijena, izvorista, odredista);
[m,n] = size(R);
jedinicnaMatrica = zeros(m,n);
for i=1:m
   for j=1:n
       if(R(i,j) ~= 0)
           jedinicnaMatrica(i,j) = 1;
       end
   end
end
[finalna] = steppingStone(matricaCijenaNova, R, jedinicnaMatrica);
set(handles.K,'string',num2str(finalna));
[m,n] = size(matricaCijenaNova);
suma = 0;
for i=1:m
   for j=1:n
       if(finalna(i,j) ~= 1e-10)
           suma = suma + matricaCijenaNova(i,j) * finalna(i,j);
       end
   end
end
set(handles.edit31,'string',num2str(suma));



function edit31_Callback(hObject, eventdata, handles)
% hObject    handle to edit31 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit31 as text
%        str2double(get(hObject,'String')) returns contents of edit31 as a double


% --- Executes during object creation, after setting all properties.
function edit31_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit31 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end





function I_Callback(hObject, eventdata, handles)
% hObject    handle to I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of I as text
%        str2double(get(hObject,'String')) returns contents of I as a double


% --- Executes during object creation, after setting all properties.
function I_CreateFcn(hObject, eventdata, handles)
% hObject    handle to I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function O_Callback(hObject, eventdata, handles)
% hObject    handle to O (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of O as text
%        str2double(get(hObject,'String')) returns contents of O as a double


% --- Executes during object creation, after setting all properties.
function O_CreateFcn(hObject, eventdata, handles)
% hObject    handle to O (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


