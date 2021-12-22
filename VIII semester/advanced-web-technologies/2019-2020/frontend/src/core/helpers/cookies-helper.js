import Cookies from 'universal-cookie';

function getCookieMethods() {
  const cookies = new Cookies();

  const setCookie = (key, value) => {
    cookies.set(key, value, { path: '/' });
  };

  const getCookie = key => {
    return cookies.get(key, { path: '/' });
  };

  const removeCookie = key => {
    cookies.remove(key, { path: '/' });
  };

  return {
    setCookie,
    getCookie,
    removeCookie,
  };
}

export default getCookieMethods();
