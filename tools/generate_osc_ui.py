import jinja2
import xml.etree.ElementTree as eT

if __name__ == '__main__':
    settings = eT.parse("../bin/data/settings.xml").getroot()
    layers = settings.find('layers')

    env = jinja2.Environment(
        loader=jinja2.FileSystemLoader("templates")
    )

    tab_template = env.get_template("layertab_template.json")
    master_template = env.get_template("master_template.json")
    tabs = []

    for i, l in enumerate(layers):
        tab_args = {
            'name': "LMG"+repr(int(i)),
            'base_address': "LMG"+repr(int(i)),
            'efx': []
        }

        for j, efx in enumerate(l.findall("efx")):
            e = {
                'index': j,
                'tab': "CONTENT"
            }

            temp = env.get_template(f"/{efx.text}.json")
            efx_args = {
                'index': repr(j)
            }
            e['tab'] = temp.render(efx_args)
            tab_args['efx'].append(e)
            print(efx.text)

        tab = tab_template.render(tab_args)
        tabs.append(tab)

    # output master render
    args = {
        'tabs': tabs
    }
    master = master_template.render(args)
    print(master)
    with open("master_output.json", "w") as f:
        f.write(master)
