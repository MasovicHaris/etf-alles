using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vicinor
{
    class ValidacijaUser
    {
        //Validacija

        public static Tuple<bool, String> validateUsernameLength(String username)
        {
            if (username.Length < 6) return new Tuple<bool,String> (false, "Username must contain atleast 6 characters!");
            return new Tuple<bool, String>(true, "");

        }

        public static Tuple<bool, String> validateUsernameContent(String username)
        {
            String p = "Username must contain atleast one number!Username can contain only lower case letters, numbers and '_'. ";
            if (!username.All(c => Char.IsLetterOrDigit(c) || c == '_')) new Tuple<bool, String>(false,p);
            if (username.Any(char.IsUpper)) new Tuple<bool, String>(false, p); //ne smije biti ni jedno veliko slovo
            if (!username.Any(char.IsNumber)) new Tuple<bool, String>(false,  p);
            return new Tuple<bool, String>(true, "");

        }

        public static Tuple<bool, String> validatePasswordLength(String password)
        {
            if (password.Length < 6) new Tuple<bool, String>(false, "Password must contain atleast 6 characters!");
            return new Tuple<bool, String>(true, "");
        }

        public static Tuple<bool, String> validatePasswordContent(String password)
        {
            String p = "Password must contain atleast one number and one UpperCase letter! Password can only contain letters, numbers and '_'. ";
            if (!password.All(c => Char.IsLetterOrDigit(c) || c == '_')) new Tuple<bool, String>(false, p);
            if (!password.Any(char.IsUpper)) new Tuple<bool, String>(false, p);
            if (!password.Any(char.IsNumber)) new Tuple<bool, String>(false, p);
            return new Tuple<bool, String>(true, "");

        }

        public static Tuple<bool, String> validatePasswordConfirmPassword(String password, String confirm)
        {
            if (String.Compare(password, confirm) == 0) return new Tuple<bool, String>(true, "");
            return new Tuple<bool, String>(false, "");
        }

        public static Tuple<bool, String> validateFirstName(String name)
        {
            if (name.Length < 6) return new Tuple<bool, String>(false, "First name must contain atleast 6 characters!");
            if (!name.All(Char.IsLetter)) return new Tuple<bool, String>(false, "First name can only contain letters!");
            Char c = name[0];
            if (Char.IsUpper(c)) return new Tuple<bool, String>(false, "First letter must be Upper case!");
            return new Tuple<bool, String>(true, "First name is valid");

        }

        public static Tuple<bool, String> validateLastName(String name)
        {
            if (name.Length < 6) return new Tuple<bool, String>(false, "Last name must contain atleast 6 characters!");
            if (!name.All(Char.IsLetter)) return new Tuple<bool, String>(false, "Last name can only contain letters!");
            Char c = name[0];
            if (Char.IsUpper(c)) return new Tuple<bool, String>(false, "Last letter must be Upper case!");
            return new Tuple<bool, String>(true, "Last name is valid");

        }

        public static Tuple<bool, String> validateEmail(String email)
        {
            if (email.Length < 6) return new Tuple<bool, String>(false, "Email contain atleast 10 characters!");
            if (!email.All(Char.IsLetter)) return new Tuple<bool, String>(false, "Email must contain @!");
            String p = "Email can only contain lower case letters, numbers and '_', '.', '@'";
            if (!email.All(c => Char.IsLetterOrDigit(c) || c == '_' || c == '.' || c == '@')) new Tuple<bool, String>(false, p);
            if (!email.Any(char.IsUpper)) new Tuple<bool, String>(false, p);
            if (!email.Any(char.IsNumber)) new Tuple<bool, String>(false, p);

            return new Tuple<bool, String>(true, "Email is valid");

        }
    }
}
