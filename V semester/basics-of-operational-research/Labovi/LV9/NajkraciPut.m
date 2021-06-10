function varargout = NajkraciPut(varargin)
% NajkraciPut M-file for NajkraciPut.fig
%      NajkraciPut, by itself, creates a new NajkraciPut or raises the existing
%      singleton*.
%
%      H = NajkraciPut returns the handle to a new NajkraciPut or the handle to
%      the existing singleton*.
%
%      NajkraciPut('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in NajkraciPut.M with the given input arguments.
%
%      NajkraciPut('Property','Value',...) creates a new NajkraciPut or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before NajkraciPut_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to NajkraciPut_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Copyright 2002-2003 The MathWorks, Inc.

% Edit the above text to modify the response to help NajkraciPut

% Last Modified by GUIDE v2.5 27-Nov-2007 12:34:18

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @NajkraciPut_OpeningFcn, ...
                   'gui_OutputFcn',  @NajkraciPut_OutputFcn, ...
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


% --- Executes just before NajkraciPut is made visible.
function NajkraciPut_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to NajkraciPut (see VARARGIN)

% Choose default command line output for NajkraciPut
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes NajkraciPut wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = NajkraciPut_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function veze_Callback(hObject, eventdata, handles)
% hObject    handle to veze (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of veze as text
%        str2double(get(hObject,'String')) returns contents of veze as a double


% --- Executes during object creation, after setting all properties.
function veze_CreateFcn(hObject, eventdata, handles)
% hObject    handle to veze (see GCBO)
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

veze  = str2num(get(handles.veze,'String'));
pocetni  = str2num(get(handles.Pocetni,'String'));


[rjesenje] = nadji_NajkraciPut(veze,pocetni);

set(handles.rjesenje,'String',num2str(rjesenje));


function rjesenje_Callback(hObject, eventdata, handles)
% hObject    handle to rjesenje (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of rjesenje as text
%        str2double(get(hObject,'String')) returns contents of rjesenje as a double


% --- Executes during object creation, after setting all properties.
function rjesenje_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rjesenje (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function min_duzina_Callback(hObject, eventdata, handles)
% hObject    handle to min_duzina (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of min_duzina as text
%        str2double(get(hObject,'String')) returns contents of min_duzina as a double


% --- Executes during object creation, after setting all properties.
function min_duzina_CreateFcn(hObject, eventdata, handles)
% hObject    handle to min_duzina (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end





function Pocetni_Callback(hObject, eventdata, handles)
% hObject    handle to Pocetni (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Pocetni as text
%        str2double(get(hObject,'String')) returns contents of Pocetni as a double


% --- Executes during object creation, after setting all properties.
function Pocetni_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Pocetni (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end


