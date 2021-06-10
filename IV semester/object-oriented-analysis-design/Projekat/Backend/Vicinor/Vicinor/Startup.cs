using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(Vicinor.Startup))]
namespace Vicinor
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
