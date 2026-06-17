
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,getRefValue,getRefValues,isTrue} from "$/utils/state"
import {Root as RadixFormRoot} from "@radix-ui/react-form"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Form_root_87a956c8c63f61744f5f8d0e80272552 = memo(({children}) => {
    

    const handleSubmit_718ef4e7b97166fe6005c4a7775ac0ba = useCallback((ev) => {
        const $form = ev.target
        ev.preventDefault()
        const form_data = {...Object.fromEntries(new FormData($form).entries()), ...({  })};

        (((...args) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.do_login", ({ ["form_data"] : form_data }), ({  })))], args, ({  }))))(ev));

        if (false) {
            $form.reset()
        }
    })
    


    return(
        jsx(RadixFormRoot,{className:"Root ",css:({ ["width"] : "100%" }),onSubmit:handleSubmit_718ef4e7b97166fe6005c4a7775ac0ba},children)
    )
});
